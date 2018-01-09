/*
 * spi_master.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include "libbase/k60/hardware.h"

#include <cassert>
#include <cstddef>
#include <cstdint>

#include <algorithm>
#include <functional>

#include "libbase/log.h"
#include "libbase/k60/clock_utils.h"
#include "libbase/k60/misc_utils.h"
#include "libbase/k60/pin.h"
#include "libbase/k60/pinout.h"
#include "libbase/k60/sim.h"
#include "libbase/k60/spi_master.h"
#include "libbase/k60/spi_utils.h"
#include "libbase/k60/vectors.h"

#include "libutil/misc.h"

using namespace libutil;
using namespace std;

#define TX_FIFO_SIZE 4

namespace libbase {
namespace k60 {

namespace {

constexpr SPI_Type* MEM_MAPS[PINOUT::GetSpiCount()] = {SPI0, SPI1, SPI2};

SpiMaster* g_instances[PINOUT::GetSpiCount()] = {};

class DelayScalerCalculator {
 public:
  void Calc(const uint32_t delay_ns);

  Uint GetBestPrescaler() const {
    return m_best_prescaler;
  }

  Uint GetBestScaler() const {
    return m_best_scaler;
  }

 private:
  Uint m_best_prescaler;
  Uint m_best_scaler;
};

void DelayScalerCalculator::Calc(const uint32_t delay_ns) {
  const Uint prescalers[] = {1, 3, 5, 7};
  const uint32_t bus_mhz = ClockUtils::GetBusClockMhz();

  m_best_prescaler = m_best_scaler = 0;
  Uint min_diff = static_cast<Uint>(-1);
  for (Uint i = 0; i < sizeof(prescalers) / sizeof(Uint); ++i) {
    for (Uint j = 0; j < 0x10; ++j) {
      const uint32_t this_delay = (prescalers[i] * (0x10 << j)) * 1000
          / bus_mhz;
      const Uint this_diff = abs((int32_t) (this_delay - delay_ns));
      if (this_diff < min_diff) {
        min_diff = this_diff;
        m_best_prescaler = i;
        m_best_scaler = j;
      }

      if (min_diff == 0) {
        break;
      }
    }
  }
}

inline void SetHalt_(const uint8_t module, const bool flag) {
  if (flag) {
    SET_BIT(MEM_MAPS[module]->MCR, SPI_MCR_HALT_SHIFT);
  } else {
    CLEAR_BIT(MEM_MAPS[module]->MCR, SPI_MCR_HALT_SHIFT);
  }
}

}

SpiMaster::SpiMaster(const Config& config)
    : m_sin(nullptr),
      m_sout(nullptr),
      m_sck(nullptr),

      m_is_init(false) {
  if (!InitModule(config) || g_instances[m_module]) {
    assert(false);
    return;
  }

  m_is_init = true;
  g_instances[m_module] = this;

#if MK60DZ10 || MK60D10
  Sim::SetEnableClockGate(EnumAdvance(Sim::ClockGate::kSpi0, m_module), true);
#elif MK60F15
  Sim::SetEnableClockGate(EnumAdvance(Sim::ClockGate::kDspi0, m_module), true);
#endif
  InitPin(config);
  InitMcrReg(config);
  InitCtarReg(config);
  InitInterrupt(config);

  SetHalt(false);
}

SpiMaster::SpiMaster(SpiMaster&& rhs)
    : SpiMaster(nullptr) {
  *this = std::move(rhs);
}

SpiMaster::SpiMaster(nullptr_t)
    : m_module(0),
      m_frame_size(0),

      m_sin(nullptr),
      m_sout(nullptr),
      m_sck(nullptr),

      m_is_init(false) {}

SpiMaster::~SpiMaster() {
  Uninit();
}

SpiMaster& SpiMaster::operator=(SpiMaster&& rhs) {
  if (this != &rhs) {
    Uninit();
    if (rhs) {
      rhs.m_is_init = false;

      m_module = rhs.m_module;

      m_sin = std::move(rhs.m_sin);
      m_sout = std::move(rhs.m_sout);
      m_sck = std::move(rhs.m_sck);
      for (Uint i = 0; i < kSlaveCount; ++i) {
        m_cs[i] = std::move(rhs.m_cs[i]);
      }

      m_frame_size = rhs.m_frame_size;

      m_is_init = true;
      g_instances[m_module] = this;
    }
  }
  return *this;
}

bool SpiMaster::InitModule(const Config& config) {
  const Spi::SinName sin = PINOUT::GetSpiSin(config.sin_pin);
  const int sin_module = (sin != Spi::SinName::kDisable)
                         ? static_cast<int>(sin) : -1;

  const Spi::SoutName sout = PINOUT::GetSpiSout(config.sout_pin);
  const int sout_module = (sout != Spi::SoutName::kDisable)
                          ? static_cast<int>(sout) : -1;

  const Spi::SckName sck = PINOUT::GetSpiSck(config.sck_pin);
  const int sck_module = static_cast<int>(sck);

  Spi::PcsName pcs = Spi::PcsName::kDisable;
  for (Uint i = 0; i < kSlaveCount; ++i) {
    const Spi::PcsName this_pcs = PINOUT::GetSpiPcs(config.slaves[i].cs_pin);
    if (this_pcs == Spi::PcsName::kDisable) {
      // Ignore, do nothing
      continue;
    }

    if (pcs != Spi::PcsName::kDisable && this_pcs != pcs) {
      return false;
    } else {
      pcs = this_pcs;
    }
  }
  const int pcs_module = SpiUtils::GetSpiModule(pcs);

  if ((sin == Spi::SinName::kDisable && sout == Spi::SoutName::kDisable)
      || sck == Spi::SckName::kDisable || pcs == Spi::PcsName::kDisable) {
    return false;
  }
  if (sin_module != sout_module && sin_module != -1 && sout_module != -1) {
    return false;
  }
  const int module = (sin_module != -1) ? sin_module : sout_module;
  if (module == -1) {
    return false;
  }
  if (module != sck_module || module != pcs_module) {
    return false;
  }

  m_module = module;
  return true;
}

void SpiMaster::InitPin(const Config& config) {
  if (config.sin_pin != Pin::Name::kDisable) {
    Pin::Config sin_config;
    sin_config.pin = config.sin_pin;
    sin_config.mux = PINOUT::GetSpiSinMux(config.sin_pin);
    m_sin = Pin(sin_config);
  }

  if (config.sout_pin != Pin::Name::kDisable) {
    Pin::Config sout_config;
    sout_config.pin = config.sout_pin;
    sout_config.mux = PINOUT::GetSpiSoutMux(config.sout_pin);
    m_sout = Pin(sout_config);
  }

  Pin::Config sck_config;
  sck_config.pin = config.sck_pin;
  sck_config.mux = PINOUT::GetSpiSckMux(config.sck_pin);
  m_sck = Pin(sck_config);

  for (Uint i = 0; i < kSlaveCount; ++i) {
    if (config.slaves[i].cs_pin == Pin::Name::kDisable) {
      break;
    }
    Pin::Config cs_config;
    cs_config.pin = config.slaves[i].cs_pin;
    cs_config.mux = PINOUT::GetSpiPcsMux(config.slaves[i].cs_pin);
    m_cs[i] = Pin(cs_config);
  }
}

void SpiMaster::InitMcrReg(const Config& config) {
  uint32_t reg = 0;

  SET_BIT(reg, SPI_MCR_MSTR_SHIFT);
  if (config.is_modified_timing) {
    SET_BIT(reg, SPI_MCR_MTFE_SHIFT);
  }
  SET_BIT(reg, SPI_MCR_ROOE_SHIFT);

  for (Uint i = 0; i < kSlaveCount; ++i) {
    if (config.slaves[i].cs_pin == Pin::Name::kDisable) {
      break;
    }
    reg |= (!config.slaves[i].is_active_high) << (SPI_MCR_PCSIS_SHIFT
        + SpiUtils::GetCsNumber(config.slaves[i].cs_pin));
  }

  SET_BIT(reg, SPI_MCR_CLR_TXF_SHIFT);
  SET_BIT(reg, SPI_MCR_CLR_RXF_SHIFT);
  // Don't start yet
  SET_BIT(reg, SPI_MCR_HALT_SHIFT);

  MEM_MAPS[m_module]->MCR = reg;
}

void SpiMaster::InitCtarReg(const Config& config) {
  assert(config.frame_size >= 4 && config.frame_size <= 16);

  uint32_t reg = 0;

  SetBaudRate(config.baud_rate_khz, &reg);
  SetPcsSckDelay(config.pcs_to_sck_delay_ns, &reg);
  SetAfterSckDelay(config.after_sck_delay_ns, &reg);
  SetAfterTransferDelay(config.after_transfer_delay_ns, &reg);

  m_frame_size = Clamp<uint8_t>(4, config.frame_size, 16);
  reg |= SPI_CTAR_FMSZ(m_frame_size - 1);
  if (!config.is_sck_idle_low) {
    SET_BIT(reg, SPI_CTAR_CPOL_SHIFT);
  }
  if (!config.is_sck_capture_first) {
    SET_BIT(reg, SPI_CTAR_CPHA_SHIFT);
  }
  if (!config.is_msb_firt) {
    SET_BIT(reg, SPI_CTAR_LSBFE_SHIFT);
  }

  MEM_MAPS[m_module]->CTAR[0] = reg;
}

void SpiMaster::InitInterrupt(const Config& config) {
  m_rx_isr = config.rx_isr;
  m_tx_isr = config.tx_isr;

  SetInterrupt((bool) m_rx_isr, (bool) m_tx_isr);
}

void SpiMaster::SetBaudRate(const uint32_t baud_rate_khz, uint32_t* reg) {
  const Uint pbrs[] = {1, 2, 3, 5, 7};
  const Uint brs[] = {2, 4, 6, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096,
                      8192, 16384, 32768};
  const uint32_t bus_khz = ClockUtils::GetBusClockKhz();

  Uint best_pbr_pos = 0, best_br_pos = 0;
  Uint min_diff = static_cast<Uint>(-1);
  for (Uint i = 0; i < sizeof(pbrs) / sizeof(Uint); ++i) {
    for (Uint j = 0; j < sizeof(brs) / sizeof(Uint); ++j) {
      const uint32_t this_baud_rate = bus_khz / (pbrs[i] * brs[j]);
      const Uint this_diff = abs((int32_t) (this_baud_rate - baud_rate_khz));
      if (this_diff < min_diff) {
        min_diff = this_diff;
        best_pbr_pos = i;
        best_br_pos = j;
      }

      if (min_diff == 0) {
        break;
      }
    }
  }

  if (best_pbr_pos == 0) {
    SET_BIT(*reg, SPI_CTAR_DBR_SHIFT);
  } else {
    *reg |= SPI_CTAR_PBR(best_pbr_pos - 1);
  }
  *reg |= SPI_CTAR_BR(best_br_pos);
}

void SpiMaster::SetPcsSckDelay(const uint32_t pcs_sck_delay_ns, uint32_t* reg) {
  DelayScalerCalculator calc;
  calc.Calc(pcs_sck_delay_ns);
  *reg |= SPI_CTAR_PCSSCK(calc.GetBestPrescaler());
  *reg |= SPI_CTAR_CSSCK(calc.GetBestScaler());
}

void SpiMaster::SetAfterSckDelay(const uint32_t after_sck_delay_ns,
                                 uint32_t* reg) {
  DelayScalerCalculator calc;
  calc.Calc(after_sck_delay_ns);
  *reg |= SPI_CTAR_PASC(calc.GetBestPrescaler());
  *reg |= SPI_CTAR_ASC(calc.GetBestScaler());
}

void SpiMaster::SetAfterTransferDelay(const uint32_t after_transfer_delay_ns,
                                      uint32_t* reg) {
  DelayScalerCalculator calc;
  calc.Calc(after_transfer_delay_ns);
  *reg |= SPI_CTAR_PDT(calc.GetBestPrescaler());
  *reg |= SPI_CTAR_DT(calc.GetBestScaler());
}

void SpiMaster::SetInterrupt(const bool tx_flag, const bool rx_flag) {
  // If we init the interrupt here, Tx isr will be called immediately which
  // may not be intended
  SetEnableRxIrq(false);
  SetEnableTxIrq(false);

  if (tx_flag || rx_flag) {
    SetIsr(EnumAdvance(SPI0_IRQn, m_module), IrqHandler);
    EnableIrq(EnumAdvance(SPI0_IRQn, m_module));
  } else {
    DisableIrq(EnumAdvance(SPI0_IRQn, m_module));
    SetIsr(EnumAdvance(SPI0_IRQn, m_module), nullptr);
  }
}

void SpiMaster::Uninit() {
  if (m_is_init) {
    m_is_init = false;

    SetHalt(true);
    SetInterrupt(false, false);

#if MK60DZ10 || MK60D10
    Sim::SetEnableClockGate(EnumAdvance(Sim::ClockGate::kSpi0, m_module),
                            false);
#elif MK60F15
    Sim::SetEnableClockGate(EnumAdvance(Sim::ClockGate::kDspi0, m_module),
            false);
#endif
    g_instances[m_module] = nullptr;
  }
}

void SpiMaster::SetHalt(const bool flag) {
  SetHalt_(m_module, flag);
}

uint16_t SpiMaster::ExchangeData(const uint8_t slave_id, const uint16_t data) {
  STATE_GUARD(SpiMaster, 0);
  if (slave_id >= kSlaveCount) {
    assert(false);
    return 0;
  }

  uint32_t reg = 0;
  reg |= SPI_PUSHR_CTAS(0);
  reg |= SPI_PUSHR_PCS(1 << SpiUtils::GetCsNumber(m_cs[slave_id].GetName()));
  reg |= SPI_PUSHR_TXDATA(data & ((1 << m_frame_size) - 1));

  // Wait until old data is gone
  while (MEM_MAPS[m_module]->SR & SPI_SR_TXCTR_MASK) {}
  MEM_MAPS[m_module]->PUSHR = reg;
  // Wait until new data is sent
  while (MEM_MAPS[m_module]->SR & SPI_SR_TXCTR_MASK) {}
  while (!(MEM_MAPS[m_module]->SR & SPI_SR_RXCTR_MASK)) {}

  uint16_t receive = 0;
  // Dismiss old data
  while (GET_BITS(MEM_MAPS[m_module]->SR, SPI_SR_RXCTR_SHIFT,
                  SPI_SR_RXCTR_MASK) > 1) {
    receive = MEM_MAPS[m_module]->POPR;
  }
  receive = MEM_MAPS[m_module]->POPR;
  return receive;
}

void SpiMaster::KickStart() {
  STATE_GUARD(SpiMaster, VOID);
  SetHalt(false);
}

size_t SpiMaster::PushData(const uint8_t slave_id, const uint16_t* data,
                           const size_t size) {
  return PushData(slave_id, reinterpret_cast<const uint8_t*>(data), size * 2);
}

size_t SpiMaster::PushData(const uint8_t slave_id, const uint8_t* data,
                           const size_t size) {
  STATE_GUARD(SpiMaster, 0);

  const size_t space = TX_FIFO_SIZE - GET_BITS(MEM_MAPS[m_module]->SR,
                                               SPI_SR_TXCTR_SHIFT, SPI_SR_TXCTR_MASK);
  if (space == 0) {
    // FIFO is full
    return 0;
  }
  const size_t send = std::min<size_t>(space, (m_frame_size > 8) ? (size / 2)
                                                                 : size);

  const uint8_t csn = SpiUtils::GetCsNumber(m_cs[slave_id].GetName());
  for (size_t i = 0; i < send; ++i) {
    uint32_t reg = 0;
    reg |= SPI_PUSHR_CTAS(0);
    reg |= SPI_PUSHR_PCS(1 << csn);
    if (m_frame_size > 8) {
      reg |= SPI_PUSHR_TXDATA(((data[i * 2] << 8) | data[i * 2 + 1])
                                  & ((1 << m_frame_size) - 1));
    } else {
      reg |= SPI_PUSHR_TXDATA(data[i] & ((1 << m_frame_size) - 1));
    }
    MEM_MAPS[m_module]->PUSHR = reg;
  }
  SET_BIT(MEM_MAPS[m_module]->SR, SPI_SR_TFFF_SHIFT);
  return send;
}

void SpiMaster::SetEnableRxIrq(const bool flag) {
  STATE_GUARD(SpiMaster, VOID);

  if (flag) {
    SET_BIT(MEM_MAPS[m_module]->RSER, SPI_RSER_RFDF_RE_SHIFT);
  } else {
    CLEAR_BIT(MEM_MAPS[m_module]->RSER, SPI_RSER_RFDF_RE_SHIFT);
  }
}

void SpiMaster::SetEnableTxIrq(const bool flag) {
  STATE_GUARD(SpiMaster, VOID);

  if (flag) {
    SET_BIT(MEM_MAPS[m_module]->RSER, SPI_RSER_TFFF_RE_SHIFT);
  } else {
    CLEAR_BIT(MEM_MAPS[m_module]->RSER, SPI_RSER_TFFF_RE_SHIFT);
  }
}

__ISR void SpiMaster::IrqHandler() {
  const int module = GetActiveIrq() - SPI0_IRQn;
  SpiMaster* const that = g_instances[module];
  if (!that || !(*that)) {
    // Something wrong?
    assert(false);
    SetHalt_(module, true);
    MEM_MAPS[module]->RSER = 0;
    return;
  }

  if (GET_BIT(MEM_MAPS[module]->RSER, SPI_RSER_TFFF_RE_SHIFT)
      && GET_BIT(MEM_MAPS[module]->SR, SPI_SR_TFFF_SHIFT)) {
    SET_BIT(MEM_MAPS[module]->SR, SPI_SR_TFFF_SHIFT);
    if (that->m_tx_isr) {
      that->m_tx_isr(that);
    } else {
      SetHalt_(module, true);
      CLEAR_BIT(MEM_MAPS[module]->RSER, SPI_RSER_TFFF_RE_SHIFT);
      SetHalt_(module, false);
    }
  }

  if (GET_BIT(MEM_MAPS[module]->RSER, SPI_RSER_RFDF_RE_SHIFT)
      && GET_BIT(MEM_MAPS[module]->SR, SPI_SR_RFDF_SHIFT)) {
    SET_BIT(MEM_MAPS[module]->SR, SPI_SR_RFDF_SHIFT);
    if (that->m_rx_isr) {
      that->m_rx_isr(that);
    } else {
      SetHalt_(module, true);
      CLEAR_BIT(MEM_MAPS[module]->RSER, SPI_RSER_RFDF_RE_SHIFT);
      SetHalt_(module, false);
    }
  }

  if (GET_BIT(MEM_MAPS[module]->RSER, SPI_RSER_TCF_RE_SHIFT)
      && GET_BIT(MEM_MAPS[module]->SR, SPI_SR_TCF_SHIFT)) {
    SET_BIT(MEM_MAPS[module]->SR, SPI_SR_TCF_SHIFT);
    SetHalt_(module, true);
  }
}

}
}
