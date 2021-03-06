/*
 * pwm.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstdint>

#include "libbase/kl26/pin.h"

namespace libbase {
namespace kl26 {

class Pwm {
 public:
  struct Config {
    enum struct Precision {
      kUs,
      kNs,
    };

    Pin::Name pin;
    uint32_t period;
    uint32_t pos_width;
    /**
     * Set the unit of Config::period and Config::pos_width. It is useful
     * when the period is too small such that the precision is not high
     * enough. Otherwise, the default should be kept
     *
     * @note Should only select Precision::kNs when period < 1000 us.
     * Otherwise integer overflow may occur during some calculations
     */
    Precision precision = Precision::kUs;
  };

  virtual ~Pwm() {}

  virtual operator bool() const = 0;

  virtual void SetPeriod(const uint32_t period, const uint32_t pos_width) = 0;
  virtual void SetPosWidth(const uint32_t pos_width) = 0;
};

}
}
