/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef HANDLE_MANAGER_H
#define HANDLE_MANAGER_H

#include <array>
#include <cstdint>

#include "kfx/Handle.h"

namespace kfx {
class HandleManager {
 public:
  HandleManager();

  Handle addEntry(void *data);
  void *getEntry(Handle handle);
  void updateEntry(Handle handle, void *data);
  void removeEntry(Handle handle);

 private:
  struct HandleEntry {
    HandleEntry()
        : m_counter(0),
          m_next_free_index(0),
          m_active(false),
          // m_end_of_list(false),
          m_data(nullptr) {}

    uint32_t m_counter : 15;
    uint32_t m_next_free_index : 16;
    uint32_t m_active : 1;
    // uint32_t m_end_of_list : 1;

    void *m_data;
  };

  std::array<HandleEntry, Handle::MAX_HANDLES> m_entries;

  uint32_t m_first_free_index;
};
}

#endif  // HANDLE_MANAGER_H
