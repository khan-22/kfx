#include "kfx/Handle.h"

namespace kfx {
Handle Handle::NULL_HANDLE;

Handle::Handle() : m_counter(0), m_index(0), m_is_initialized(false) {}

Handle::Handle(uint32_t counter, uint32_t index)
    : m_counter(counter), m_index(index), m_is_initialized(true) {}

Handle::operator uint32_t() {
  return m_is_initialized << 31 | m_index << 15 | m_counter;
}

// Handle::operator bool() { return static_cast<uint32_t>(*this); }
}