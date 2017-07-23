/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <array>

#include "Components.h"
#include "Handle.h"

namespace kfx {
class GameObject {
 public:
  // void addComponent(ComponentType type, Handle handle);
  Handle getComponent(ComponentType type);
  bool hasComponent(ComponentType type);

 private:
  std::array<Handle, ComponentType::NUM_TYPES> m_components;

  friend class GameObjectFactory;
};
}

#endif  // GAME_OBJECT_H
