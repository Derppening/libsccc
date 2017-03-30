/*
 * pin_isr_manager.cpp
 * Manage ISR for ports
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cassert>
#include <cstring>

#include <bitset>
#include <functional>

#include "libbase/kl26/misc_utils.h"
#include "libbase/kl26/pin.h"
#include "libbase/kl26/pin_isr_manager.h"
#include "libbase/kl26/pin_utils.h"
#include "libbase/kl26/vectors.h"

#include "libutil/misc.h"

using namespace libbase::kl26;
using namespace libutil;

namespace libbase {
namespace kl26 {

PinIsrManager* PinIsrManager::m_instance = nullptr;

PinIsrManager* PinIsrManager::GetInstance() {
  if (!m_instance) {
    m_instance = new PinIsrManager;
  }
  return m_instance;
}

PinIsrManager::PinIsrManager() {
  for (Uint i = 0; i < PINOUT::GetPortCount(); ++i) {
    m_pin_data[i] = nullptr;
    m_is_enable[i] = false;
  }
}

PinIsrManager::~PinIsrManager() {
  for (Uint i = 0; i < PINOUT::GetPortCount(); ++i) {
    if (m_is_enable[i]) {
      SetIsr(EnumAdvance(PORTA_IRQn, i), DefaultIsr);
      DisableIrq(EnumAdvance(PORTA_IRQn, i));
    }
    if (m_pin_data[i]) {
      delete[] m_pin_data[i];
    }
  }
}

void PinIsrManager::InitPort(const Uint port) {
  if (port != 0 && port != 2 && port != 3) {
    // Port not interruptable
    assert(false);
    return;
  }

  if (!m_pin_data[port]) {
    m_pin_data[port] = new PinData[PINOUT::GetPortPinCount()];
    memset(m_pin_data[port], 0, PINOUT::GetPortPinCount() * sizeof(PinData));
  }

  switch (port) {
    case 0:
      SetIsr(PORTA_IRQn, PortIrqHandler<0>);
      EnableIrq(PORTA_IRQn);
      break;

    case 2:
    case 3:
      SetIsr(PORTC_PORTD_IRQn, PortIrqHandler<2>);
      EnableIrq(PORTC_PORTD_IRQn);
      break;

/*	case 3:
		SetIsr(PORTC_PORTD_IRQn, PortIrqHandler<3>);
		EnableIrq(PORTC_PORTD_IRQn);
		break;*/
  }
  m_is_enable[port] = true;
}

void PinIsrManager::SetPinIsr_(Pin* pin, const OnPinIrqListener& isr) {
  const Uint port = PinUtils::GetPort(pin->GetName());
  const Uint pin_num = PinUtils::GetPinNumber(pin->GetName());
  if (isr) {
    if (!m_is_enable[port]) {
      InitPort(port);
    }
    m_pin_data[port][pin_num].pin = nullptr;
    m_pin_data[port][pin_num].isr = isr;
    m_pin_data[port][pin_num].pin = pin;
  } else if (m_is_enable[port]) {
    m_pin_data[port][pin_num].pin = nullptr;
    m_pin_data[port][pin_num].isr = nullptr;

    // Disable interrupt only if all are null
    for (Uint i = 0; i < PINOUT::GetPortPinCount(); ++i) {
      if (m_pin_data[port][i].isr) {
        return;
      }
    }
    SetIsr(EnumAdvance(PORTA_IRQn, port), DefaultIsr);
    DisableIrq(EnumAdvance(PORTA_IRQn, port));
    m_is_enable[port] = false;
  }
}

template<Uint port>
__ISR void PinIsrManager::PortIrqHandler() {
  PinData* pin_data = PinIsrManager::GetInstance()->m_pin_data[port];
  for (Uint i = 0; i < PINOUT::GetPortPinCount(); ++i) {
    const Pin::Name pin = PinUtils::GetPin(port, i);
    if (Pin::IsInterruptRequested(pin)) {
      if (pin_data[i].pin && pin_data[i].isr) {
        pin_data[i].isr(pin);
      }
      Pin::ConsumeInterrupt(pin);
    }
  }
  /*
   * Consume Port D Isrs on PORTC_PORTD_IRQn
   */
  if (port == 2) {
    pin_data = PinIsrManager::GetInstance()->m_pin_data[port + 1];
    for (Uint i = 0; i < PINOUT::GetPortPinCount(); ++i) {
      const Pin::Name pin = PinUtils::GetPin(port + 1, i);
      if (Pin::IsInterruptRequested(pin)) {
        if (pin_data[i].pin && pin_data[i].isr) {
          pin_data[i].isr(pin);
        }
        Pin::ConsumeInterrupt(pin);
      }
    }
  }
}

}
}

