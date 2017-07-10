/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef LISTENER_INTERFACE_H
#define LISTENER_INTERFACE_H

#include "kfx/Message.h"

namespace kfx {
class ListenerInterface {
 public:
  virtual ~ListenerInterface() = default;

  virtual void tell(Message message) = 0;

 protected:
  ListenerInterface() = default;

 private:
};
}

#endif  // LISTENER_INTERFACE_H
