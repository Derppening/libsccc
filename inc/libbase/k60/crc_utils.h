/*
 * crc_utils.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include "libbase/k60/crc.h"
#include "libbase/k60/misc_utils.h"

namespace libbase {
namespace k60 {

class CrcUtils {
 public:
  static uint32_t Calc(Crc* crc, const Byte* data, const size_t size);
};

}
}
