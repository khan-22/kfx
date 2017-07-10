/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef LISTENER_H
#define LISTENER_H

#include "kfx/Message.h"

namespace kfx {
class Listener {
 public:
  Listener() = default;
  virtual ~Listener() = default;

  virtual void tell(Message message) = 0;

 private:
};
}

#endif  // LISTENER_H
