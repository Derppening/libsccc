/*
 * soft_quad_decoder.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include "libbase/k60/gpio.h"
#include "libbase/k60/quad_decoder_interface.h"

namespace libbase {
namespace k60 {

/**
 * Software emulated quadrature decoding using pin interrupt and GPIO. In K60
 * under Phase AB mode, the encoder resolution will be extended to 4 times the
 * original when using hardware quadrature decoding. We emulate this behavior by
 * multiplying the current count by 4 in software mode, so there will be a
 * maximum of +-3 error
 */
class SoftQuadDecoder : public QuadDecoderInterface {
 public:
  struct Config : public QuadDecoderInterface::Config {
    /**
     * @see FtmQuadDecoder::Config::EncodingMode
     */
    enum struct EncodingMode {
      kPhaseAB,
      kCountDirection,
    };

    EncodingMode encoding_mode;
  };

  explicit SoftQuadDecoder(const Config& config);
  explicit SoftQuadDecoder(nullptr_t);
  SoftQuadDecoder(const SoftQuadDecoder&) = delete;
  SoftQuadDecoder(SoftQuadDecoder&& rhs);
  ~SoftQuadDecoder();

  SoftQuadDecoder& operator=(const SoftQuadDecoder&) = delete;
  SoftQuadDecoder& operator=(SoftQuadDecoder&& rhs);
  operator bool() const override {
    return m_is_init;
  }

  int32_t GetCount() override;
  void ResetCount() override;

 private:
  void Uninit();

  void OnTick(Gpi*);

  bool m_is_invert_a_polarity;
  bool m_is_invert_b_polarity;
  bool m_is_dir_mode;

  Gpi m_qda;
  Gpi m_qdb;

  volatile int32_t m_count;

  bool m_is_init;
};

}
}
