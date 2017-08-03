/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace kfx {

namespace StandardEventMessage {
enum Type {
  TEST1,
  TEST2,

  DEBUG,

  KEY_ACTION,

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

EVENT_ARGUMENT_DATA(StandardEventMessage::KEY_ACTION) {
  int action;
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};
}

#endif  // MESSAGE_H
