/*
 * ftm.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include "libbase/k60/hardware.h"

#include <cassert>

#include <algorithm>

#include "libbase/k60/ftm_utils.h"
#include "libbase/k60/pinout.h"
#include "libbase/misc_types.h"

namespace libbase {
namespace k60 {

Ftm::Ftm() {
  for (Uint i = 0; i < PINOUT_FTM_COUNT; ++i) {
    m_module_lock[i] = ModuleLockMode::kFree;
    for (Uint j = 0; j < PINOUT_FTM_CHANNEL_COUNT; ++j) {
      m_channel_lock[i][j] = false;
    }
  }
}

bool Ftm::RegFtm(const Ftm::Name ftm, const bool is_exclusive_module) {
  const Uint module = FtmUtils::GetFtmModule(ftm);
  const Uint channel = FtmUtils::GetFtmChannel(ftm);
  assert(module < PINOUT_FTM_COUNT);
  assert(channel < PINOUT_FTM_CHANNEL_COUNT);
  if (m_module_lock[module] == ModuleLockMode::kExclusive) {
    return false;
  } else if (m_module_lock[module] == ModuleLockMode::kShared
      && is_exclusive_module) {
    return false;
  } else if (m_channel_lock[module][channel]) {
    return false;
  }

  m_module_lock[module] = is_exclusive_module ? ModuleLockMode::kExclusive
                                              : ModuleLockMode::kShared;
  m_channel_lock[module][channel] = true;
  return true;
}

bool Ftm::UnregFtm(const Ftm::Name ftm) {
  const Uint module = FtmUtils::GetFtmModule(ftm);
  const Uint channel = FtmUtils::GetFtmChannel(ftm);
  assert(module < PINOUT_FTM_COUNT);
  assert(channel < PINOUT_FTM_CHANNEL_COUNT);
  m_channel_lock[module][channel] = false;

  for (bool l : m_channel_lock[PINOUT_FTM_COUNT]) {
    if (l) {
      return false;
    }
  }
  m_module_lock[module] = ModuleLockMode::kFree;
  return true;
}

}
}
