#include "kfx/GameObjectFactory.h"

#include <iostream>

#include "kfx/Assert.h"

namespace kfx {
GameObjectFactory::GameObjectFactory(MeshManager &mesh_manager,
                                     ShaderManager &shader_manager,
                                     TextureManager &texture_manager,
                                     MaterialManager &material_manager,
                                     TransformSystem &transform_system,
                                     MeshSystem &mesh_system)
    : m_mesh_manager(mesh_manager),
      m_shader_manager(shader_manager),
      m_texture_manager(texture_manager),
      m_material_manager(material_manager),
      m_transform_system(transform_system),
      m_mesh_system(mesh_system) {
  // ...
}

GameObject GameObjectFactory::addGameObject() {
  //
  GameObject new_object;

  // TEMPORARY
  new_object.index = m_game_objects.size();
  new_object.counter = 0;
  m_game_objects.emplace_back(new_object);

  return new_object;
}

void GameObjectFactory::removeGameObject(GameObject game_object) {
  //
}

GameObject GameObjectFactory::createTestObject() {
  // // Create GameObject and components
  // Handle object_handle = m_game_objects.addResourceEntry();
  // Handle transform_component_handle =
  //     addComponent(object_handle, ComponentType::TRANSFORM);
  // Handle mesh_component_handle =
  //     addComponent(object_handle, ComponentType::MESH);

  // // Get Components
  // // TransformComponent *transform_component =
  // //     m_transform_components.getResourceEntry(transform_component_handle);

  // MeshComponent *mesh_component =
  //     m_mesh_components.getResourceEntry(mesh_component_handle);

  // // Set up components
  // mesh_component->mesh_handle = m_mesh_manager.getMeshByName("test");
  // mesh_component->material_handle =
  //     m_material_manager.getMaterialByName("test-material");
  // // mesh_component->shader_handle =
  // // m_shader_manager.getShaderByName("basic");
  // // mesh_component->texture_handle =
  // // m_texture_manager.getTextureByName("test");
  // kfx_contract(mesh_component->mesh_handle != Handle::NULL_HANDLE);

  // // Return object handle
  // return object_handle;

  GameObject object = addGameObject();

  m_transform_system.addTransform(object, glm::vec3(3.f, 0.f, 0.f),
                                  glm::vec3(0.f, 0.f, 0.f));
  m_mesh_system.addMesh(object, m_mesh_manager.getMeshByName("test"),
                        m_material_manager.getMaterialByName("test-material"));

  return object;
}

// HandledResource<GameObject> &GameObjectFactory::getGameObjects() {
//   return m_game_objects;
// }

// HandledResource<TransformComponent>
//     &GameObjectFactory::getTransformComponents() {
//   return m_transform_components;
// }

// HandledResource<MeshComponent> &GameObjectFactory::getMeshComponents() {
//   return m_mesh_components;
// }

// Handle GameObjectFactory::addComponent(Handle game_object_handle,
//                                        ComponentType component_type) {
//   kfx_contract(component_type >= 0);
//   kfx_contract(component_type < ComponentType::NUM_TYPES);
//   kfx_contract(game_object_handle.m_is_initialized == true);

//   GameObject *game_object =
//   m_game_objects.getResourceEntry(game_object_handle);
//   if (!game_object->hasComponent(component_type)) {
//     Handle component_handle = Handle::NULL_HANDLE;

//     switch (component_type) {
//       case ComponentType::TRANSFORM:
//         component_handle = m_transform_components.addResourceEntry();
//         break;
//       case ComponentType::MESH:
//         component_handle = m_mesh_components.addResourceEntry();
//         break;
//       default:
//         std::cerr << "A COMPONENT TYPE WAS NOT IMPLEMENTED IN " <<
//         __FUNCTION__
//                   << std::endl;
//         abort();
//         break;
//     }

//     game_object->m_components[component_type] = component_handle;

//     return component_handle;
//   } else {
//     return game_object->getComponent(component_type);
//   }
// }

// void GameObjectFactory::removeComponent(Handle game_object_handle,
//                                         ComponentType component_type) {
//   kfx_contract(component_type >= 0);
//   kfx_contract(component_type < ComponentType::NUM_TYPES);
//   kfx_contract(game_object_handle.m_is_initialized == true);

//   GameObject *game_object =
//   m_game_objects.getResourceEntry(game_object_handle);
//   if (game_object->hasComponent(component_type)) {
//     Handle component_handle = game_object->getComponent(component_type);

//     switch (component_type) {
//       case ComponentType::TRANSFORM:
//         m_transform_components.removeResourceEntry(component_handle);
//         break;
//       case ComponentType::MESH:
//         m_mesh_components.removeResourceEntry(component_handle);
//         break;
//       default:
//         std::cerr << "A COMPONENT TYPE WAS NOT IMPLEMENTED IN " <<
//         __FUNCTION__
//                   << std::endl;
//         abort();
//         break;
//     }

//     game_object->m_components[component_type] = Handle::NULL_HANDLE;
//   }
// }
}
