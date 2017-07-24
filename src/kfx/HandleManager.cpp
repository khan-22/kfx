#include "kfx/HandleManager.h"

#include "kfx/Assert.h"

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
  kfx_assert(m_first_free_index != Handle::MAX_HANDLES);

  uint32_t index = m_first_free_index;
  m_first_free_index = m_entries[index].m_next_free_index;
  kfx_assert(m_entries[index].m_active == false);

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
  kfx_assert(handle.m_is_initialized == true);

  kfx_assert(handle.m_index >= 0);
  kfx_assert(handle.m_index < Handle::MAX_HANDLES);
  kfx_assert(m_entries[handle.m_index].m_active == true);

  kfx_assert(handle.m_counter == m_entries[handle.m_index].m_counter);

  return m_entries[handle.m_index].m_data;
}

void HandleManager::updateEntry(Handle handle, void* data) {
  kfx_assert(handle.m_is_initialized == true);

  kfx_assert(handle.m_index >= 0);
  kfx_assert(handle.m_index < Handle::MAX_HANDLES);
  kfx_assert(m_entries[handle.m_index].m_active == true);

  m_entries[handle.m_index].m_data = data;
}

void HandleManager::removeEntry(Handle handle) {
  kfx_assert(handle.m_is_initialized == true);

  kfx_assert(handle.m_index >= 0);
  kfx_assert(handle.m_index < Handle::MAX_HANDLES);
  kfx_assert(m_entries[handle.m_index].m_active == true);

  m_entries[handle.m_index].m_active = false;
  m_entries[handle.m_index].m_data = nullptr;
}
}
