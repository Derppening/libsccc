/*
 * uart_device.cpp
 *
 * Author: Ming Tsang
 * Copyright (c) 2014-2015 HKUST SmartCar Team
 * Refer to LICENSE for details
 */

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <functional>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "libbase/log.h"
#include "libbase/helper.h"
#include "libbase/misc_types.h"
#include LIBBASE_H(pin)
#include LIBBASE_H(uart)

#include "libsc/config.h"
#include "libsc/kl26/uart_device.h"
#include "libutil/misc.h"

using namespace LIBBASE_NS;
using namespace libutil;
using namespace std;

#define RX_BUFFER_SIZE 128

namespace libsc {
namespace kl26 {

#ifdef LIBSC_USE_UART

struct UartDevice::RxBuffer {
  RxBuffer()
      : start(0), end(0) {
    memset(data, 0, RX_BUFFER_SIZE);
  }

  uint32_t GetSize() const volatile {
    return (uint32_t) (end - start);
  }

  Byte data[RX_BUFFER_SIZE];
  uint32_t start;
  uint32_t end;
};

class UartDevice::TxBuffer {
 public:
  struct Block {
    Block(Byte* const data, const size_t size, const bool is_mem_owned)
        : type(kByteAry),
          size(size),
          it(0),
          is_mem_owned(is_mem_owned) {
      this->data.byte_ = data;
    }

    Block(Byte* const data, const size_t size)
        : Block(data, size, true) {}

    explicit Block(std::string* const data)
        : type(kString),
          size(data->size()),
          it(0),
          is_mem_owned(true) {
      this->data.string_ = data;
    }

    explicit Block(std::vector<Byte>* const data)
        : type(kVector),
          size(data->size()),
          it(0),
          is_mem_owned(true) {
      this->data.vector_ = data;
    }

    Block()
        : type(kByteAry),
          size(0),
          it(0),
          is_mem_owned(false) {
      this->data.byte_ = nullptr;
    }

    Block(const Block&) = delete;
    Block(Block&& rhs)
        : data(rhs.data),
          type(rhs.type),
          size(rhs.size),
          it(rhs.it),
          is_mem_owned(rhs.is_mem_owned) {
      rhs.data.byte_ = nullptr;
      rhs.is_mem_owned = false;
    }

    ~Block() {
      Recycle();
    }

    Block& operator=(const Block&) = delete;
    Block& operator=(Block&& rhs);

    void Recycle();

    union {
      Byte* byte_;
      std::string* string_;
      std::vector<Byte>* vector_;
    } data;
    enum : uint8_t {
      kByteAry,
      kString,
      kVector,
    } type;
    size_t size;
    volatile uint8_t it;
    bool is_mem_owned;
  };

  explicit TxBuffer(const size_t capacity)
      : m_capacity(capacity),
        m_data(new Block[capacity]),
        m_start(0),
        m_end(0) {}

  uint32_t GetSize() const {
    return (uint32_t) (m_end - m_start);
  }

  bool PushBlock(Block&& block);
  Block* GetActiveBlock();
  Block* NextBlock();

 private:
  const size_t m_capacity;
  unique_ptr<Block[]> m_data;
  volatile uint32_t m_start;
  volatile uint32_t m_end;
};

UartDevice::TxBuffer::Block& UartDevice::TxBuffer::Block::operator=(Block&& rhs) {
  if (this != &rhs) {
    Byte* const data_ = rhs.data.byte_;
    bool is_mem_owned_ = rhs.is_mem_owned;
    Recycle();
    rhs.data.byte_ = nullptr;
    rhs.is_mem_owned = false;

    data.byte_ = data_;
    type = rhs.type;
    size = rhs.size;
    it = rhs.it;
    is_mem_owned = is_mem_owned_;
  }
  return *this;
}

void UartDevice::TxBuffer::Block::Recycle() {
  if (is_mem_owned && data.byte_) {
    switch (type) {
      case kByteAry:
        delete[] data.byte_;
        break;

      case kString:
        delete data.string_;
        break;

      case kVector:
        delete data.vector_;
        break;

      default:
        assert(false);
    }
    data.byte_ = nullptr;
  }
}

bool UartDevice::TxBuffer::PushBlock(Block&& block) {
  if (GetSize() == m_capacity) {
    return false;
  } else {
    m_data[m_end++ % m_capacity] = std::move(block);
    return true;
  }
}

UartDevice::TxBuffer::Block* UartDevice::TxBuffer::GetActiveBlock() {
  if (GetSize() == 0) {
    return nullptr;
  } else {
    return &m_data[m_start % m_capacity];
  }
}

UartDevice::TxBuffer::Block* UartDevice::TxBuffer::NextBlock() {
  if (GetSize() == 0) {
    return nullptr;
  } else {
    ++m_start;
    return GetActiveBlock();
  }
}

namespace {

#if LIBSC_USE_UART == 1
inline Pin::Name GetTxPin(const uint8_t) {
  return LIBSC_UART0_TX;
}

inline Pin::Name GetRxPin(const uint8_t) {
  return LIBSC_UART0_RX;
}

#else
inline Pin::Name GetTxPin(const uint8_t id)
{
    switch (id)
    {
    default:
        assert(0);

    case 0:
        return LIBSC_UART0_TX;

#if LIBSC_USE_UART > 1
    case 1:
        return LIBSC_UART1_TX;
#endif
    }
}

inline Pin::Name GetRxPin(const uint8_t id)
{
    switch (id)
    {
    default:
        assert(0);

    case 0:
        return LIBSC_UART0_RX;

#if LIBSC_USE_UART > 1
    case 1:
        return LIBSC_UART1_RX;
#endif
    }
}

#endif

inline Uart::Config GetUartConfig_(Uart::Config&& config,
                                   const Uart::OnTxEmptyListener& tx_isr,
                                   const Uart::OnRxFullListener& rx_isr) {
  config.tx_isr = tx_isr;
  config.rx_isr = rx_isr;
  return config;
}

}

Uart::Config UartDevice::Initializer::GetUartConfig() const {
  Uart::Config product;
  product.tx_pin = GetTxPin(config.id);
  product.rx_pin = GetRxPin(config.id);
  product.baud_rate = config.baud_rate;
  return product;
}

UartDevice::UartDevice(const Initializer& initializer)
    : m_rx_buf{new RxBuffer},
      m_rx_isr(initializer.config.rx_isr),
      m_tx_buf(new TxBuffer(initializer.config.tx_buf_size)),
      m_is_tx_idle(true),
      m_uart(nullptr) {
  Uart::Config&& uart_config = initializer.GetUartConfig();
  uart_config.rx_isr = std::bind(&UartDevice::OnRxFull, this, placeholders::_1);
  uart_config.tx_isr = std::bind(&UartDevice::OnTxEmpty, this,
                                 placeholders::_1);
  m_uart = Uart(uart_config);

  m_uart.SetEnableRxIrq(true);
}

UartDevice::~UartDevice() {}

inline void UartDevice::EnableTx() {
  if (m_is_tx_idle) {
    m_is_tx_idle = false;
    m_uart.SetEnableTxIrq(true);
  }
}

inline void UartDevice::DisableTx() {
  m_uart.SetEnableTxIrq(false);
  m_is_tx_idle = true;
}

bool UartDevice::SendStr(const char* str) {
  const size_t size = strlen(str);
  if (size == 0) {
    return true;
  }
  Byte* data = new Byte[size];
  memcpy(data, str, size);

  if (m_tx_buf->PushBlock(TxBuffer::Block(data, size))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendStr(unique_ptr<char[]>&& str) {
  const size_t size = strlen(str.get());
  if (size == 0) {
    return true;
  }

  if (m_tx_buf->PushBlock(TxBuffer::Block(reinterpret_cast<Byte*>(str.release()),
                                          size))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendStr(string&& str) {
  if (str.size() == 0) {
    return true;
  }

  if (m_tx_buf->PushBlock(TxBuffer::Block(new string(std::move(str))))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendBuffer(const Byte* buf, const size_t len) {
  if (len == 0) {
    return true;
  }
  Byte* data = new Byte[len];
  memcpy(data, buf, len);

  if (m_tx_buf->PushBlock(TxBuffer::Block(data, len))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendBuffer(unique_ptr<Byte[]>&& buf, const size_t len) {
  if (len == 0) {
    return true;
  }

  if (m_tx_buf->PushBlock(TxBuffer::Block(buf.release(), len))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendBuffer(vector<Byte>&& buf) {
  if (buf.size() == 0) {
    return true;
  }

  if (m_tx_buf->PushBlock(TxBuffer::Block(new vector<Byte>(std::move(buf))))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

bool UartDevice::SendStrLiteral(const char* str) {
  const size_t size = strlen(str);
  if (size == 0) {
    return true;
  }

  if (m_tx_buf->PushBlock(TxBuffer::Block((Byte*) str, size, false))) {
    EnableTx();
    return true;
  } else {
    return false;
  }
}

void UartDevice::OnTxEmpty(Uart* uart) {
  TxBuffer::Block* block = m_tx_buf->GetActiveBlock();
  while (block && block->it == block->size) {
    block = m_tx_buf->NextBlock();
  }
  if (!block) {
    DisableTx();
    return;
  }

  switch (block->type) {
    case TxBuffer::Block::kByteAry:
      uart->PutByte(*(block->data.byte_ + block->it++));
      break;

    case TxBuffer::Block::kString:
      uart->PutByte(*((const Byte*) block->data.string_->data() + block->it++));
      break;

    case TxBuffer::Block::kVector:
      uart->PutByte(*(block->data.vector_->data() + block->it++));
      break;
  }
}

bool UartDevice::PeekChar(char* out_char) {
  if (m_rx_buf->GetSize() == 0) {
    return false;
  }

  *out_char = m_rx_buf->data[m_rx_buf->start++ % RX_BUFFER_SIZE];
  return true;
}

void UartDevice::OnRxFull(Uart* uart) {
  Byte byte;
  if (!uart->PeekByte(&byte)) {
    return;
  }

  if (!m_rx_isr || !m_rx_isr(byte)) {
    if (m_rx_buf->GetSize() + 1 < RX_BUFFER_SIZE) {
      m_rx_buf->data[m_rx_buf->end++ % RX_BUFFER_SIZE] = byte;
    }
  }
}

#else /* LIBSC_USE_UART */

struct UartDevice::RxBuffer
{};

struct UartDevice::TxBuffer
{};

UartDevice::UartDevice(const Initializer&)
        : UartDevice(nullptr)
{}
UartDevice::UartDevice(nullptr_t)
        : m_is_tx_idle(true), m_uart(nullptr)
{
    LOG_DL("Configured not to use UartDevice");
}
UartDevice::~UartDevice() {}
bool UartDevice::SendStr(const char*) { return false; }
bool UartDevice::SendStr(unique_ptr<char[]>&&) { return false; }
bool UartDevice::SendStr(string&&) { return false; }
bool UartDevice::SendBuffer(const Byte*, const size_t) { return false; }
bool UartDevice::SendBuffer(unique_ptr<Byte[]>&&, const size_t) { return false; }
bool UartDevice::SendBuffer(vector<Byte>&&) { return false; }
bool UartDevice::PeekChar(char*) { return false; }

#endif /* LIBSC_USE_UART */

}
}
