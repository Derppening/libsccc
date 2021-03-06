/*
 * encoder.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include "libbase/helper.h"
#include "libbase/pinout_macros.h"
#include LIBBASE_H(gpio)
#include LIBBASE_H(soft_quad_decoder)

#if PINOUT_FTM_COUNT
#include LIBBASE_H(ftm_quad_decoder)

#elif PINOUT_TPM_COUNT
#include LIBBASE_H(tpm_quad_decoder)

#else
#define LIBSC_USE_SOFT_ENCODER 1

#endif // PINOUT_FTM_COUNT

#include "libsc/config.h"

namespace libsc {

class Encoder {
 public:
#if LIBSC_USE_SOFT_ENCODER
  typedef LIBBASE_MODULE(SoftQuadDecoder) QuadDecoder;

#elif PINOUT_FTM_COUNT
  typedef LIBBASE_MODULE(FtmQuadDecoder) QuadDecoder;

#elif PINOUT_TPM_COUNT
  typedef LIBBASE_MODULE(TpmQuadDecoder) QuadDecoder;

#endif // LIBSC_USE_SOFT_ENCODER

  struct Config {
    uint8_t id;
  };

  virtual ~Encoder();

  void Update();

  /**
   * Return the decoded count
   *
   * @return
   */
  int32_t GetCount() const {
    return m_count;
  }

 protected:
  /**
   * Use to initialize the encoder in possibly a polymorphic way, notice that
   * Initializer::config is stored as a reference only
   */
  struct Initializer {
    explicit Initializer(const Config& config)
        : config(config) {}

    virtual QuadDecoder::Config GetQuadDecoderConfig() const;

    const Config& config;
  };

  explicit Encoder(const Initializer& initializer);
  explicit Encoder(nullptr_t);
  Encoder(Encoder&& rhs);

 private:
  int32_t m_count;

  QuadDecoder m_quad_decoder;
};

}
