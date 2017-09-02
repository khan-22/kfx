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
#include <variant>

#include "kfx/GameObject.h"

#include "kfx/Handle.h"

namespace kfx {

struct Test1 {
  std::string message;
};

struct Test2 {
  std::string message;
};

struct Debug {
  std::string message;
};

struct KeyAction {
  int action;
  int key;
  int scancode;
  int mods;

  bool shiftPressed() { return mods & GLFW_MOD_SHIFT; }
  bool ctrlPressed() { return mods & GLFW_MOD_CONTROL; }
  bool altPressed() { return mods & GLFW_MOD_ALT; }
  bool superPressed() { return mods & GLFW_MOD_SUPER; }
};

struct RenderMesh {
  glm::mat4 world_transform;
  Handle mesh;
  Handle material;
  // Handle shader;
  // Handle texture;
};

struct UpdatedWorldTransform {
  GameObject object;
  glm::mat4 world_transform;
};

// ...

#define IMPL_MESSAGE_TYPES \
  Test1, Test2, Debug, KeyAction, RenderMesh, UpdatedWorldTransform

using Message = std::variant<IMPL_MESSAGE_TYPES>;

namespace detail {
template <typename... TArgs>
constexpr std::size_t tArgCount() {
  return sizeof...(TArgs);
}
}

constexpr std::size_t numberOfMessageTypes() {
  return detail::tArgCount<IMPL_MESSAGE_TYPES>();
}
}

#endif  // MESSAGE_H
