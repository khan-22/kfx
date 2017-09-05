#include "kfx/GameObjectFactory.h"

#include <iostream>

#include "kfx/Assert.h"

namespace kfx {
GameObjectFactory::GameObjectFactory(MeshManager &mesh_manager,
                                     ShaderManager &shader_manager,
                                     TextureManager &texture_manager,
                                     MaterialManager &material_manager,
                                     TransformSystem &transform_system,
                                     MeshSystem &mesh_system,
                                     FpsInputSystem &fps_input_system)
    : m_mesh_manager(mesh_manager),
      m_shader_manager(shader_manager),
      m_texture_manager(texture_manager),
      m_material_manager(material_manager),
      m_transform_system(transform_system),
      m_mesh_system(mesh_system),
      m_fps_input_system(fps_input_system) {
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
  GameObject game_object = addGameObject();

  m_transform_system.addTransform(game_object, glm::vec3(3.f, 0.f, 0.f),
                                  glm::vec3(0.f, 0.f, 0.f));
  m_mesh_system.addMesh(game_object, m_mesh_manager.getMeshByName("test"),
                        m_material_manager.getMaterialByName("test-material"));

  m_fps_input_system.addFpsControls(game_object);

  return game_object;
}

GameObject GameObjectFactory::createStaticObject(std::string mesh_name,
                                                 std::string material_name,
                                                 glm::vec3 position) {
  GameObject game_object = addGameObject();

  m_transform_system.addTransform(game_object, position, glm::vec3(0.f));
  m_mesh_system.addMesh(game_object, m_mesh_manager.getMeshByName(mesh_name),
                        m_material_manager.getMaterialByName(material_name));

  return game_object;
}
}
