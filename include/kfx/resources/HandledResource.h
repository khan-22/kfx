/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef HANDLED_RESOURCE_H
#define HANDLED_RESOURCE_H

#include <algorithm>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/HandleManager.h"
#include "kfx/resources/Resource.h"

namespace kfx {
template <typename T>
class HandledResource {
 public:
  void validate_handles();

  std::vector<Resource<T>> resource;

  Handle addResourceEntry();
  T* getResourceEntry(Handle handle);
  void removeResourceEntry(Handle handle);

 private:
  HandleManager m_handle_manager;
  Resource<T>* m_previous_data_pointer = nullptr;
};

template <typename T>
void HandledResource<T>::validate_handles() {
  // If the data pointer has changed, all handles most likely
  // need to be updated to point to the new location in memory
  if (resource.data() != m_previous_data_pointer) {
    for (auto& r : resource) {
      m_handle_manager.updateEntry(r.handle, &r);
    }
    m_previous_data_pointer = resource.data();
  }
}

template <typename T>
Handle HandledResource<T>::addResourceEntry() {
  resource.emplace_back();
  Resource<T>& new_resource = resource.back();

  Handle new_handle = m_handle_manager.addEntry(&new_resource);
	new_resource.handle = new_handle;

  validate_handles();
  return new_handle;
}

template <typename T>
T* HandledResource<T>::getResourceEntry(Handle handle) {
  return &static_cast<Resource<T>*>(m_handle_manager.getEntry(handle))->value;
}

template <typename T>
void HandledResource<T>::removeResourceEntry(Handle handle) {
  auto it =
      std::find_if(resource.begin(), resource.end(),
                   [&handle](Resource<T>& a) { return a.handle == handle; });

  if (it != resource.end()) {
    resource.erase(it);

    m_handle_manager.removeEntry(handle);
    validate_handles();
  }
}
}
#endif  // HANDLED_RESOURCE_H
