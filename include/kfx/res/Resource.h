/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef RESOURCE_H
#define RESOURCE_H

#include "kfx/Handle.h"

namespace kfx {
template <typename T>
struct Resource final {
 public:
  template <typename... MArgs>
  Resource(MArgs&&... mArgs);

  Handle handle;
  T value;
};

template <typename T>
template <typename... MArgs>
Resource<T>::Resource(MArgs&&... mArgs)
    : handle(Handle::NULL_HANDLE), value(std::forward<MArgs>(mArgs)...) {
  //...
}
}
#endif  // RESOURCE_H
