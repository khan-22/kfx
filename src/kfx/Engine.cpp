#include "kfx/Engine.h"

namespace kfx {
Engine::Engine(Window& window)
    : m_window(window),
      m_game_object_factory(m_mesh_manager, m_shader_manager, m_texture_manager,
                            m_material_manager),
      m_keyboard_input_manager(m_message_box, window),
      m_renderer3d(m_message_box, *this),
      m_material_manager(m_shader_manager, m_texture_manager) {
  m_window.setGLFWUserData(this);
}

void Engine::init() {
  // ...

  m_systems.push_back(std::make_unique<GraphicsSystem3D>(m_message_box, this));
}

void Engine::update(float dt) {
  m_message_box.distributeMessages();

  for (auto& system : m_systems) {
    system->update(dt);
  }

  m_message_box.distributeMessages();
}

void Engine::render() {
  // ...
  m_window.clear();

  m_renderer3d.render();

  m_window.swapBuffers();
}

Window& Engine::getWindow() {
  return m_window;  // <-
}

MessageBox& Engine::getMessageBox() {
  return m_message_box;  // <-
}

MeshManager& Engine::getMeshManager() {
  return m_mesh_manager;  // <-
}

ShaderManager& Engine::getShaderManager() {
  return m_shader_manager;  // <-
}

TextureManager& Engine::getTextureManager() {
  return m_texture_manager;  // <-
}

MaterialManager& Engine::getMaterialManager() {
  return m_material_manager;  // <-
}

KeyboardInputPeripheral& Engine::getKeyboardInputPeripheral() {
  return m_keyboard_input_manager;  // <-
}

GameObjectFactory& Engine::getGameObjectFactory() {
  return m_game_object_factory;  // <-
}
}
