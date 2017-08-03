/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace kfx {

namespace StandardEventMessage {
enum Type {
  TEST1,
  TEST2,

  DEBUG,

  NUM_TYPES,
  CUSTOM_MESSAGE_EXTENSION = NUM_TYPES
};
}

namespace detail {
// A common base struct that allows storing pointers to data members of
// different type
struct EventArgumentDataBase {};
}

template <StandardEventMessage::Type T>
struct EventArgumentData : public detail::EventArgumentDataBase {};

#define EVENT_ARGUMENT_DATA(enum) \
  template <>                     \
  struct EventArgumentData<enum>

EVENT_ARGUMENT_DATA(StandardEventMessage::TEST1) { std::string message; };

EVENT_ARGUMENT_DATA(StandardEventMessage::TEST2) { std::string message; };

EVENT_ARGUMENT_DATA(StandardEventMessage::DEBUG) { std::string message; };
}

#endif  // MESSAGE_H
