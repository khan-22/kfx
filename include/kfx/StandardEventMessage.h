/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "kfx/Handle.h"

namespace kfx {

namespace StandardEventMessage {
enum Type {
  TEST1,
  TEST2,

  DEBUG,

  KEY_ACTION,

  RENDER_MESH,

  NUM_TYPES,
  CUSTOM_MESSAGE_EXTENSION = NUM_TYPES
};
}

namespace detail {
// A common base struct that allows storing pointers to data members of
// different type
struct EventArgumentDataBase {
  virtual ~EventArgumentDataBase() = default;
};
}

template <StandardEventMessage::Type T>
struct EventArgumentData : public detail::EventArgumentDataBase {
  virtual ~EventArgumentData<T>() final override = default;
};

#define EVENT_ARGUMENT_DATA(enum) \
  template <>                     \
  struct EventArgumentData<enum> : public detail::EventArgumentDataBase

#define EVENT_ARGUMENT_DESTRUCTOR(enum) \
  ~EventArgumentData<enum>() final override = default;

EVENT_ARGUMENT_DATA(StandardEventMessage::TEST1) {
  EVENT_ARGUMENT_DESTRUCTOR(StandardEventMessage::TEST1);
  std::string message;
};

EVENT_ARGUMENT_DATA(StandardEventMessage::TEST2) {
  EVENT_ARGUMENT_DESTRUCTOR(StandardEventMessage::TEST2);
  std::string message;
};

EVENT_ARGUMENT_DATA(StandardEventMessage::DEBUG) {
  EVENT_ARGUMENT_DESTRUCTOR(StandardEventMessage::DEBUG);
  std::string message;
};

EVENT_ARGUMENT_DATA(StandardEventMessage::KEY_ACTION) {
  EVENT_ARGUMENT_DESTRUCTOR(StandardEventMessage::KEY_ACTION);
  int action;
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};

EVENT_ARGUMENT_DATA(StandardEventMessage::RENDER_MESH) {
  EVENT_ARGUMENT_DESTRUCTOR(StandardEventMessage::RENDER_MESH);
  glm::mat4 model_transform;
  Handle mesh;
  Handle material;
  // Handle shader;
  // Handle texture;
};
}

#endif  // MESSAGE_H
