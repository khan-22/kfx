#include "kfx/Engine.h"

namespace kfx {
Engine::Engine() : m_game_object_factory(m_mesh_manager, m_shader_manager) {}

void Engine::init() {
  // ...

  m_systems.push_back(std::make_unique<GraphicsSystem3D>(this));
}

void Engine::update(float dt) {
  for (auto& system : m_systems) {
    system->update(dt);
  }
}

void Engine::render() {
  // ...
}

GameObjectFactory& Engine::getGameObjectFactory() {
  return m_game_object_factory;  // <-
}

MeshManager& Engine::getMeshManager() {
  return m_mesh_manager;  // <-
}

ShaderManager& Engine::getShaderManager() {
  return m_shader_manager;  // <-
}
}
