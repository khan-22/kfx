/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef LISTENER_H
#define LISTENER_H

#include "kfx/Message.h"
#include "kfx/MessageBox.h"

namespace kfx {
class Listener {
 public:
  virtual void tell(Message message) = 0;

 protected:
  Listener(MessageBox& message_box) : m_message_box(message_box) {}
  virtual ~Listener() = default;

  MessageBox& m_message_box;
};
}

#endif  // LISTENER_H
