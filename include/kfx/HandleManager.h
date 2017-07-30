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

#pragma once

#ifndef HANDLE_MANAGER_H
#define HANDLE_MANAGER_H

#include <array>
#include <cstdint>

#include "kfx/Handle.h"

namespace kfx {
class HandleManager final {
 public:
  HandleManager();

  Handle addEntry(void *data);
  void *getEntry(Handle handle);
  void updateEntry(Handle handle, void *data);
  void removeEntry(Handle handle);

  bool isFull() const;

 private:
  struct HandleEntry {
    HandleEntry()
        : m_counter(0),
          m_next_free_index(0),
          m_active(false),
          m_end_of_list(false),
          m_data(nullptr) {}

    uint32_t m_counter : 15;
    uint32_t m_next_free_index : 12;
    uint32_t m_active : 1;
    uint32_t m_end_of_list : 1;

    void *m_data;
  };

  std::array<HandleEntry, Handle::MAX_HANDLES> m_entries;

  uint32_t m_first_free_index;
  uint32_t m_number_of_entries;
};
}

#endif  // HANDLE_MANAGER_H
