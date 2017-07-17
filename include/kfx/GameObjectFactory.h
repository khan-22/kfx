/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <vector>

#include "kfx/Components.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/HandleManager.h"

#include "kfx/resources/MeshManager.h"

#include "kfx/resources/HandledResource.h"

namespace kfx {
class GameObjectFactory {
 public:
  GameObjectFactory(MeshManager& mesh_manager);

  Handle createTestObject();

  HandledResource<GameObject>& getGameObjects();

  HandledResource<TransformComponent>& getTransformComponents();
  HandledResource<MeshComponent>& getMeshComponents();

 private:
  HandledResource<GameObject> m_game_objects;

  HandledResource<TransformComponent> m_transform_components;
  HandledResource<MeshComponent> m_mesh_components;

  MeshManager& m_mesh_manager;
};
}
#endif  // GAME_OBJECT_FACTORY_H
