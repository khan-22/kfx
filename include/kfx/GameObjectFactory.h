/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <vector>

#include "Components.h"
#include "GameObject.h"
#include "Handle.h"
#include "HandleManager.h"

namespace kfx {
class GameObjectFactory {
 public:
  Handle createTestObject();

  HandleManager& getHandleManager();
  std::vector<GameObject>& getGameObjects();

 private:
  std::vector<GameObject> m_game_objects;
  std::vector<TransformComponent> m_transform_components;

  HandleManager m_handle_manager;
};
}
#endif  // GAME_OBJECT_FACTORY_H
