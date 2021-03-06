/*
 * gpio.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include "libbase/kl26/hardware.h"

#include <cassert>
#include <cstddef>
#include <cstdint>

#include <bitset>
#include <functional>

#include "libbase/log.h"
#include "libbase/kl26/gpio.h"
#include "libbase/kl26/misc_utils.h"
#include "libbase/kl26/pin.h"
#include "libbase/kl26/pin_isr_manager.h"
#include "libbase/kl26/pin_utils.h"
#include "libbase/kl26/pinout.h"

#include "libutil/misc.h"

using namespace libutil;

namespace libbase {
namespace kl26 {

namespace {

constexpr FGPIO_Type* MEM_MAPS[PINOUT::GetPortCount()] = {FPTA, FPTB, FPTC, FPTD,
                                                          FPTE};

Pin::Config GetPinConfig(const Gpi::Config& config) {
  Pin::Config pin_config;
  pin_config.pin = config.pin;
  pin_config.mux = Pin::Config::MuxControl::kGpio;
  pin_config.interrupt = config.interrupt;
  pin_config.config = config.config;
  return pin_config;
}

Pin::Config GetPinConfig(const Gpo::Config& config) {
  Pin::Config pin_config;
  pin_config.pin = config.pin;
  pin_config.mux = Pin::Config::MuxControl::kGpio;
  pin_config.config = config.config;
  return pin_config;
}

}

Gpi::Gpi(const Gpi::Config& config)
    : m_pin(GetPinConfig(config)) {
  RESET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDDR,
            PinUtils::GetPinNumber(m_pin.GetName()));
  SetIsr(config.isr);
}

Gpi::Gpi(Gpi&& rhs)
    : Gpi(nullptr) {
  *this = std::move(rhs);
}

Gpi::Gpi(Pin&& rhs)
    : m_pin(std::move(rhs)) {
  RESET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDDR,
            PinUtils::GetPinNumber(m_pin.GetName()));
}

Gpi::Gpi(nullptr_t)
    : m_pin(nullptr) {}

Gpi::~Gpi() {
  Uninit();
}

Gpi& Gpi::operator=(Gpi&& rhs) {
  if (this != &rhs) {
    Uninit();
    if (rhs) {
      OnGpiEventListener isr = rhs.m_isr;
      rhs.SetIsr(nullptr);

      m_pin = std::move(rhs.m_pin);
      SetIsr(isr);
    }
  }
  return *this;
}

void Gpi::Uninit() {
  if (m_pin) {
    SetIsr(nullptr);
    m_pin = Pin(nullptr);
  }
}

void Gpi::SetIsr(const OnGpiEventListener& isr) {
  if (m_isr) {
    PinIsrManager::SetPinIsr(&m_pin, nullptr);
  }
  m_isr = isr;
  if (m_isr) {
    PinIsrManager::SetPinIsr(&m_pin, [this](const Pin::Name) {
      m_isr(this);
    });
  }
}

bool Gpi::Get() const {
  STATE_GUARD(Gpi, false);

  return GET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDIR,
                 PinUtils::GetPinNumber(m_pin.GetName()));
}

Gpo Gpi::ToGpo() {
  STATE_GUARD(Gpo, Gpo(nullptr));

  SetIsr(nullptr);
  return Gpo(std::move(m_pin));
}

Gpo::Gpo(const Gpo::Config& config)
    : m_pin(GetPinConfig(config)) {
  SET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDDR,
          PinUtils::GetPinNumber(m_pin.GetName()));
  Set(config.is_high);
}

Gpo::Gpo(Gpo&& rhs)
    : Gpo(nullptr) {
  *this = std::move(rhs);
}

Gpo::Gpo(Pin&& rhs)
    : m_pin(std::move(rhs)) {
  SET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDDR,
          PinUtils::GetPinNumber(m_pin.GetName()));
}

Gpo::Gpo(nullptr_t)
    : m_pin(nullptr) {}

Gpo::~Gpo() {
  Uninit();
}

Gpo& Gpo::operator=(Gpo&& rhs) {
  if (this != &rhs) {
    Uninit();
    if (rhs) {
      m_pin = std::move(rhs.m_pin);
    }
  }
  return *this;
}

void Gpo::Uninit() {
  if (m_pin) {
    m_pin = Pin(nullptr);
  }
}

void Gpo::Set(bool is_high) {
  STATE_GUARD(Gpo, VOID);

  if (is_high) {
    SET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PSOR,
            PinUtils::GetPinNumber(m_pin.GetName()));
  } else {
    SET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PCOR,
            PinUtils::GetPinNumber(m_pin.GetName()));
  }
}

void Gpo::Turn() {
  STATE_GUARD(Gpo, VOID);

  SET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PTOR,
          PinUtils::GetPinNumber(m_pin.GetName()));
}

bool Gpo::Get() const {
  return GET_BIT(MEM_MAPS[PinUtils::GetPort(m_pin.GetName())]->PDOR,
                 PinUtils::GetPinNumber(m_pin.GetName()));
}

Gpi Gpo::ToGpi() {
  STATE_GUARD(Gpo, Gpi(nullptr));

  return Gpi(std::move(m_pin));
}

Gpio::Gpio(const Gpi::Config& config)
    : m_gpi(config), m_gpo(nullptr), m_is_gpo(false) {
  assert(!config.isr);
}

Gpio::Gpio(const Gpo::Config& config)
    : m_gpi(nullptr), m_gpo(config), m_is_gpo(true) {}

Gpio::Gpio(Gpio&& rhs)
    : Gpio(nullptr) {
  *this = std::move(rhs);
}

Gpio::Gpio(nullptr_t)
    : m_gpi(nullptr), m_gpo(nullptr), m_is_gpo(true) {}

Gpio::~Gpio() {
  Uninit();
}

Gpio& Gpio::operator=(Gpio&& rhs) {
  if (this != &rhs) {
    Uninit();
    if (rhs) {
      m_gpi = std::move(rhs.m_gpi);
      m_gpo = std::move(rhs.m_gpo);
      m_is_gpo = rhs.m_is_gpo;
    }
  }
  return *this;
}

void Gpio::Uninit() {
  if (m_gpi) {
    m_gpi = Gpi(nullptr);
  } else if (m_gpo) {
    m_gpo = Gpo(nullptr);
  }
}

void Gpio::EnsureGpi() {
  STATE_GUARD(Gpio, VOID);

  if (m_is_gpo) {
    m_gpi = m_gpo.ToGpi();
    m_is_gpo = false;
  }
}

void Gpio::EnsureGpo() {
  STATE_GUARD(Gpio, VOID);

  if (!m_is_gpo) {
    m_gpo = m_gpi.ToGpo();
    m_is_gpo = true;
  }
}

}
}
