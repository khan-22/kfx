/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>

#include "kfx/MessageBox.h"

#include "kfx/GameObjectFactory.h"

#include "kfx/system/System.h"

#include "kfx/system/GraphicsSystem3D.h"

#include "kfx/resources/MeshManager.h"
#include "kfx/resources/ShaderManager.h"

#include "kfx/KeyboardInputPeripheral.h"
#include "kfx/Window.h"

namespace kfx {
class Engine {
 public:
  Engine(Window& window);
  virtual ~Engine() = default;

  virtual void init();

  virtual void update(float dt);
  virtual void render();

  Window& getWindow();

  MessageBox& getMessageBox();

  MeshManager& getMeshManager();
  ShaderManager& getShaderManager();

  KeyboardInputPeripheral& getKeyboardInputPeripheral();

  GameObjectFactory& getGameObjectFactory();

 protected:
  std::vector<std::unique_ptr<System>> m_systems;

  // "Outside" references
  Window& m_window;

  // Message Box
  MessageBox m_message_box;

  // Resource managers
  MeshManager m_mesh_manager;
  ShaderManager m_shader_manager;

  // Peripherals
  KeyboardInputPeripheral m_keyboard_input_manager;

  // Factory
  GameObjectFactory m_game_object_factory;
};
}
#endif  // ENGINE_H
