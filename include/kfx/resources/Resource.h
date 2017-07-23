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
  Handle handle;
  T value;
};
}
#endif  // RESOURCE_H
