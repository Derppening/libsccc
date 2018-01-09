/*
 * trs_d05.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cstdint>

#include "libsc/trs_d05.h"

// 300 Hz
#define PERIOD 3333
#define POS_WIDTH_MIN 1500 - 900
#define POS_WIDTH_MAX 1500 + 900

namespace libsc {

namespace {

Servo::Config GetServoConfig(const uint8_t id) {
  Servo::Config config;
  config.id = id;
  config.period = PERIOD;
  config.min_pos_width = POS_WIDTH_MIN;
  config.max_pos_width = POS_WIDTH_MAX;
  return config;
}

}

TrsD05::TrsD05(const Config& config)
    : Servo(GetServoConfig(config.id)) {}

}
