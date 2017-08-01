/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef STANDARD_OBSERVER_MESSAGE_H
#define STANDARD_OBSERVER_MESSAGE_H

#include <GLFW/glfw3.h>

/*
  This file contains all the standard types of messages that can be
  sent to observers.

  (As far as I know) I had to do it this way to also make it extensible
  by other users who would hopefully simply need to start their enum
  with CUSTOM_MESSAGE_EXTENSION.

  The void* data field of the ObserverArgument allows the subject to
  send any kind of data, though for more complex collections that might
  include first defining a special kind of struct with data.
*/

namespace kfx {
enum StandardObserverMessage {
  TEST1,  // Test messages, may be removed at some other point
  TEST2,  // Test messages, may be removed at some other point

  KEY_PRESSED,
  KEY_REPEAT,
  KEY_RELEASED,

  CUSTOM_MESSAGE_EXTENSION
};

/*
  By using templates I can allow users to gain
  data in a more standardized way.

  While being somewhat error prone (since void* allows any kind
  of data), this hopefully helps to mitigate such errors by letting
  observers simply cast the void* to a ObserverArgumentData<MESSAGE_ENUM>
  where MESSAGE_ENUM is the message type they expected / recieved.
*/

template <StandardObserverMessage T>
struct ObserverArgumentData {};

#define ARGUMENT_DATA(enum) \
  template <>               \
  struct ObserverArgumentData<enum>

ARGUMENT_DATA(TEST1) { int a; };

ARGUMENT_DATA(TEST2) {
  int a;
  int b;
};

ARGUMENT_DATA(KEY_PRESSED) {
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};

ARGUMENT_DATA(KEY_REPEAT) {
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};

ARGUMENT_DATA(KEY_RELEASED) {
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};
}

#endif  // STANDARD_OBSERVER_MESSAGE_H
