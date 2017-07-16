/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef HANDLE_H
#define HANDLE_H

#include <cstdint>

namespace kfx {
struct Handle {
  Handle();
  Handle(uint32_t counter, uint32_t index);

  // Bitfield.
  uint32_t m_counter : 15;
  uint32_t m_index : 16;
  uint32_t m_is_initialized : 1;

  static const uint32_t MAX_HANDLES = 65536;  // 2^16
};
}

#endif  // HANDLE_H
