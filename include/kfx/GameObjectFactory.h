/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <vector>

// #include "kfx/Components.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/HandleManager.h"

#include "kfx/resources/MaterialManager.h"
#include "kfx/resources/MeshManager.h"
#include "kfx/resources/ShaderManager.h"
#include "kfx/resources/TextureManager.h"

#include "kfx/resources/HandledResource.h"

#include "kfx/system/FpsInputSystem.h"
#include "kfx/system/MeshSystem.h"
#include "kfx/system/TransformSystem.h"

namespace kfx {
class GameObjectFactory {
 public:
  GameObjectFactory(MeshManager& mesh_manager, ShaderManager& shader_manager,
                    TextureManager& texture_manager,
                    MaterialManager& material_manager,
                    TransformSystem& transform_system, MeshSystem& mesh_system,
                    FpsInputSystem& fps_input_system);

  GameObject addGameObject();
  void removeGameObject(GameObject game_object);

  GameObject createTestObject();

  GameObject createStaticObject(std::string mesh_name,
                                std::string material_name, glm::vec3 position);

  // HandledResource<GameObject>& getGameObjects();

  // HandledResource<TransformComponent>& getTransformComponents();
  // HandledResource<MeshComponent>& getMeshComponents();

  // Handle addComponent(Handle game_object_handle, ComponentType
  // component_type);
  // void removeComponent(Handle game_object_handle, ComponentType
  // component_type);

 protected:
  std::vector<GameObject> m_game_objects;
  // HandledResource<GameObject> m_game_objects;

  // HandledResource<TransformComponent> m_transform_components;
  // HandledResource<MeshComponent> m_mesh_components;

  MeshManager& m_mesh_manager;
  ShaderManager& m_shader_manager;
  TextureManager& m_texture_manager;
  MaterialManager& m_material_manager;

  TransformSystem& m_transform_system;
  MeshSystem& m_mesh_system;
  FpsInputSystem& m_fps_input_system;
};
}
#endif  // GAME_OBJECT_FACTORY_H
