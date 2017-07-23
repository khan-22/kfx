/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef HANDLE_H
#define HANDLE_H

#include <cstdint>

namespace kfx {
struct Handle final {
  Handle();
  Handle(uint32_t counter, uint32_t index);

  // Bitfield.
  uint32_t m_counter : 15;
  uint32_t m_index : 12;
  uint32_t m_is_initialized : 1;

  static const uint32_t MAX_HANDLES = 4096;  // 2^12

  operator uint32_t();
  // operator bool();

  static Handle NULL_HANDLE;
};
}

#endif  // HANDLE_H
