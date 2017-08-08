/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "kfx/Components.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/HandleManager.h"

#include "kfx/resources/MeshManager.h"
#include "kfx/resources/ShaderManager.h"
#include "kfx/resources/TextureManager.h"

#include "kfx/resources/HandledResource.h"

namespace kfx {
class GameObjectFactory {
 public:
  GameObjectFactory(MeshManager& mesh_manager, ShaderManager& shader_manager,
                    TextureManager& texture_manager);

  Handle createTestObject();

  HandledResource<GameObject>& getGameObjects();

  HandledResource<TransformComponent>& getTransformComponents();
  HandledResource<MeshComponent>& getMeshComponents();

  Handle addComponent(Handle game_object_handle, ComponentType component_type);
  void removeComponent(Handle game_object_handle, ComponentType component_type);

 protected:
  HandledResource<GameObject> m_game_objects;

  HandledResource<TransformComponent> m_transform_components;
  HandledResource<MeshComponent> m_mesh_components;

  MeshManager& m_mesh_manager;
  ShaderManager& m_shader_manager;
  TextureManager& m_texture_manager;
};
}
#endif  // GAME_OBJECT_FACTORY_H
