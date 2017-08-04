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
  MessageArgument() : type(type), data(nullptr) {}

  template <StandardEventMessage::Type T>
  void init();

  template <StandardEventMessage::Type T>
  EventArgumentData<T>* getDataPointer();

  uint32_t type;
  std::unique_ptr<detail::EventArgumentDataBase> data;
};

template <StandardEventMessage::Type T>
void MessageArgument::init() {
  type = T;
  data = std::make_unique<EventArgumentData<T>>();
}

template <StandardEventMessage::Type T>
EventArgumentData<T>* MessageArgument::getDataPointer() {
  return reinterpret_cast<EventArgumentData<T>*>(data.get());
}

// -------

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
