/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>

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

  GameObjectFactory& getGameObjectFactory();

  MeshManager& getMeshManager();
  ShaderManager& getShaderManager();

  KeyboardInputPeripheral& getKeyboardInputPeripheral();

  Window& getWindow();

 protected:
  std::vector<std::unique_ptr<System>> m_systems;

  GameObjectFactory m_game_object_factory;

  MeshManager m_mesh_manager;
  ShaderManager m_shader_manager;

  Window& m_window;

  KeyboardInputPeripheral m_keyboard_input_manager;
};
}
#endif  // ENGINE_H
