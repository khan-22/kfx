/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <memory>

#include "kfx/MessageBox.h"
#include "kfx/StandardEventMessage.h"

namespace kfx {

class EventListener {
 public:
  virtual void tell(Message& msg) = 0;

 protected:
  EventListener(MessageBox& message_box) : m_message_box(message_box) {}
  virtual ~EventListener() = default;

  MessageBox& m_message_box;
};
}

#endif  // EVENT_LISTENER_H
