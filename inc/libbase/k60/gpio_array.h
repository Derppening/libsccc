/*
 * gpio_array.h
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#pragma once

#include <cstddef>
#include <cstdint>

#include <vector>

#include "libbase/k60/gpio.h"

namespace libbase {
namespace k60 {

/**
 * A continuous set of GPI pins doing parallel IO. A non byte-aligned set will
 * result in pre- and post- padding of bits. Also, beware of the native
 * endianess of the chip
 */
class GpiArray {
 public:
  struct Config {
    /// The beginning pin of the set
    Pin::Name start_pin;
    /**
     * The number of pins in the set, such that (Config::start_pin
     * + Config::count) == (end_pin - 1)
     */
    uint8_t count;
    /**
     * The config to be applied to all pins
     *
     * @see Pin::Config::ConfigBit
     */
    std::bitset<Pin::Config::ConfigBit::kSize> config;
  };

  explicit GpiArray(const Config& config);
  explicit GpiArray(nullptr_t);
  GpiArray(GpiArray&& rhs);
  ~GpiArray();

  GpiArray& operator=(const GpiArray&) = delete;
  GpiArray& operator=(GpiArray&& rhs);
  operator bool() const {
    return !m_pins.empty();
  }

  /**
   * Return the data in a bit array
   *
   * @param out_data The bit array to store the data, each byte contains 8
   * bits
   * @param size The size of the array in byte
   */
  void Get(Byte* out_data, size_t size) const;

  Gpi* GetChild(const uint8_t position) {
    return &m_pins[position];
  }

  size_t GetSize() const {
    return m_pins.size();
  }

  /**
   * Config this GpiArray up to be ready to serve as DMA source, and set
   * @a config accordingly. The following options are also set besides src:<br>
   * Dma::Config::minor_bytes = 1~4 (depending on Config::count)<br>
   * Dma::Config::major_count = 1
   *
   * Notice that Gpi value is byte-aligned when working with DMA, so that if
   * Config::start_pin is not the 0/8/16/24th pin, the data received would be
   * pre-padded with data from other pins. Similarly, the data would be
   * post-padded if Config::start_pin + Config::count does not fit in 1/2/3/4
   * byte boundary
   *
   * @param config
   */
  void ConfigValueAsDmaSrc(Dma::Config* config);

 private:
  void Uninit();

  void* GetSrcAddress() const;

  std::vector<Gpi> m_pins;
};

}
}
