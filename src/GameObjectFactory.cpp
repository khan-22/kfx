#include "kfx/GameObjectFactory.h"

#include <iostream>

namespace kfx {
GameObjectFactory::GameObjectFactory(MeshManager &mesh_manager,
                                     ShaderManager &shader_manager)
    : m_mesh_manager(mesh_manager), m_shader_manager(shader_manager) {
  // ...
}

Handle GameObjectFactory::createTestObject() {
  // Create component handles
  Handle transform_component_handle = m_transform_components.addResourceEntry();
  Handle mesh_component_handle = m_mesh_components.addResourceEntry();

  // Get Components
  TransformComponent *transform_component =
      m_transform_components.getResourceEntry(transform_component_handle);

  MeshComponent *mesh_component =
      m_mesh_components.getResourceEntry(mesh_component_handle);

  // Set up components
  mesh_component->mesh_handle = m_mesh_manager.getMeshByName("test");
  mesh_component->shader_handle = m_shader_manager.getShaderByName("basic");
  assert(mesh_component->mesh_handle != Handle::NULL_HANDLE);

  // Create GameObject
  Handle object_handle = m_game_objects.addResourceEntry();

  // Add component handles to object
  GameObject *object = m_game_objects.getResourceEntry(object_handle);
  object->addComponent(ComponentType::TRANSFORM, transform_component_handle);
  object->addComponent(ComponentType::MESH, mesh_component_handle);

  // Return object handle
  return object_handle;
}

HandledResource<GameObject> &GameObjectFactory::getGameObjects() {
  return m_game_objects;
}

HandledResource<TransformComponent>
    &GameObjectFactory::getTransformComponents() {
  return m_transform_components;
}

HandledResource<MeshComponent> &GameObjectFactory::getMeshComponents() {
  return m_mesh_components;
}
}
