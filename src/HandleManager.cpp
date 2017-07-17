#include "kfx/HandleManager.h"

#include <cassert>

namespace kfx {
HandleManager::HandleManager() : m_first_free_index(0) {
  for (uint32_t i = 0; i < Handle::MAX_HANDLES; i++) {
    m_entries[i] = HandleEntry();
    m_entries[i].m_next_free_index = i + 1;
  }

  // Necessary? Just check if next free is == MAX_HANDLES.
  // m_entries[Handle::MAX_HANDLES - 1].m_end_of_list = true;
}

Handle HandleManager::addEntry(void* data) {
  assert(m_first_free_index != Handle::MAX_HANDLES);

  uint32_t index = m_first_free_index;
  m_first_free_index = m_entries[index].m_next_free_index;
  assert(m_entries[index].m_active == false);

  m_entries[index].m_counter = m_entries[index].m_counter + 1;
  m_entries[index].m_next_free_index = 0;
  m_entries[index].m_active = true;
  m_entries[index].m_data = data;

  return Handle(m_entries[index].m_counter, index);
}

void* HandleManager::getEntry(Handle handle) {
  // if (handle.m_index == Handle::MAX_HANDLES) {
  //   return nullptr;
  // }
  assert(handle.m_is_initialized == true);

  assert(handle.m_index >= 0);
  assert(handle.m_index < Handle::MAX_HANDLES);
  assert(m_entries[handle.m_index].m_active == true);

  assert(handle.m_counter == m_entries[handle.m_index].m_counter);

  return m_entries[handle.m_index].m_data;
}

void HandleManager::updateEntry(Handle handle, void* data) {
  assert(handle.m_is_initialized == true);

  assert(handle.m_index >= 0);
  assert(handle.m_index < Handle::MAX_HANDLES);
  assert(m_entries[handle.m_index].m_active == true);

  m_entries[handle.m_index].m_data = data;
}

void HandleManager::removeEntry(Handle handle) {
  assert(handle.m_is_initialized == true);

  assert(handle.m_index >= 0);
  assert(handle.m_index < Handle::MAX_HANDLES);
  assert(m_entries[handle.m_index].m_active == true);

  m_entries[handle.m_index].m_active = false;
  m_entries[handle.m_index].m_data = nullptr;
}
}
