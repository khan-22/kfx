/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Power of Two Games LLC nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY POWER OF TWO GAMES LLC ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL POWER OF TWO GAMES LLC BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
  Comment from KFX creator:
  This implementation of the handle manager is heavily based of off the
  implementation made by Power of Two, with some slight differences such as
  custom implementations of certain methods.
*/

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
