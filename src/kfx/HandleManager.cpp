#include "kfx/HandleManager.h"

#include "kfx/Assert.h"

namespace kfx {
HandleManager::HandleManager() : m_first_free_index(0), m_number_of_entries(0) {
  for (uint32_t i = 0; i < Handle::MAX_HANDLES; i++) {
    m_entries[i] = HandleEntry();
    m_entries[i].m_next_free_index = i + 1;
  }

  m_entries[Handle::MAX_HANDLES - 1].m_end_of_list = true;
}

Handle HandleManager::addEntry(void* data) {
  if (isFull()) {
    return Handle::NULL_HANDLE;
  }

  uint32_t index = m_first_free_index;
  HandleEntry& entry = m_entries[index];
  m_first_free_index = entry.m_next_free_index;
  kfx_contract(m_entries[index].m_active == false);

  entry.m_counter = m_entries[index].m_counter + 1;
  entry.m_next_free_index = 0;
  entry.m_active = true;
  entry.m_data = data;

  entry.m_end_of_list = false;

  ++m_number_of_entries;

  return Handle(m_entries[index].m_counter, index);
}

void* HandleManager::getEntry(Handle handle) {
  kfx_contract(handle.m_is_initialized == true);
  kfx_contract(m_entries[handle.m_index].m_active == true);
  kfx_contract(handle.m_counter == m_entries[handle.m_index].m_counter);

  return m_entries[handle.m_index].m_data;
}

void HandleManager::updateEntry(Handle handle, void* data) {
  kfx_contract(handle.m_is_initialized == true);
  kfx_contract(m_entries[handle.m_index].m_active == true);
  kfx_contract(handle.m_counter == m_entries[handle.m_index].m_counter);

  m_entries[handle.m_index].m_data = data;
}

void HandleManager::removeEntry(Handle handle) {
  kfx_contract(handle.m_is_initialized == true);
  kfx_contract(m_entries[handle.m_index].m_active == true);
  kfx_contract(handle.m_counter == m_entries[handle.m_index].m_counter);

  HandleEntry& entry = m_entries[handle.m_index];

  entry.m_active = false;
  entry.m_data = nullptr;

  if (isFull()) {
    entry.m_end_of_list = true;
    m_first_free_index = handle.m_index;
  } else if (m_first_free_index > handle.m_index) {
    entry.m_next_free_index = m_first_free_index;
    m_first_free_index = handle.m_index;
  } else {
    uint32_t other_index = handle.m_index - 1;
    while (m_entries[other_index].m_next_free_index < handle.m_index)
      other_index--;

    HandleEntry& other_entry = m_entries[other_index];

    entry.m_next_free_index = other_entry.m_next_free_index;
    other_entry.m_next_free_index = handle.m_index;
    if (other_entry.m_end_of_list == true) {
      entry.m_end_of_list = true;
      other_entry.m_end_of_list = false;
    }
  }

  --m_number_of_entries;
}

bool HandleManager::isFull() const {
  return m_number_of_entries == Handle::MAX_HANDLES;
}
}
