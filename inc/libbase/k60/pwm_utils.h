/*
 * pwm_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

#include "libbase/misc_types.h"

namespace libbase {
namespace k60 {

class PwmUtils {
 public:
  static uint32_t GetPeriodUs(const uint32_t frequency) {
    return 1000000 / frequency;
  }

  static uint32_t GetPeriodNs(const uint32_t frequency) {
    return 1000000000 / frequency;
  }

  static uint32_t GetPosWidth(const uint32_t period, const Uint duty_1000) {
    return period * duty_1000 / 1000;
  }
};

}
}
