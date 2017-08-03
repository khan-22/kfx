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

struct MessageArgument {
  MessageArgument(StandardEventMessage::Type type)
      : type(type), data(new detail::EventArgumentDataBase) {}

  uint32_t type;
  std::unique_ptr<detail::EventArgumentDataBase> data;
};

class EventListener {
 public:
  virtual void tell(MessageArgument& arg) = 0;

 protected:
  EventListener(MessageBox& message_box) : m_message_box(message_box) {}
  virtual ~EventListener() = default;

  MessageBox& m_message_box;
};
}

#endif  // EVENT_LISTENER_H
