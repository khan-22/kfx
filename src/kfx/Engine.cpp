#include "kfx/Engine.h"

namespace kfx {
Engine::Engine(Window& window)
    : m_window(window),
      m_game_object_factory(m_mesh_manager, m_shader_manager),
      m_keyboard_input_manager(window) {
  m_window.setGLFWUserData(this);
}

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

KeyboardInputPeripheral& Engine::getKeyboardInputPeripheral() {
  return m_keyboard_input_manager;  // <-
}

Window& Engine::getWindow() {
  return m_window;  // <-
}
}
