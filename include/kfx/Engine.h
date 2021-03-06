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

/** Managers **/
#include "kfx/resources/MeshManager.h"

#include "kfx/resources/ShaderManager.h"

#include "kfx/resources/TextureManager.h"

#include "kfx/resources/MaterialManager.h"
/** -------- **/

#include "kfx/KeyboardInputPeripheral.h"
#include "kfx/Window.h"

#include "kfx/graphics/Renderer3D.h"

#include "kfx/system/MeshSystem.h"
#include "kfx/system/TransformSystem.h"

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
  TextureManager& getTextureManager();
  MaterialManager& getMaterialManager();

  KeyboardInputPeripheral& getKeyboardInputPeripheral();

  GameObjectFactory& getGameObjectFactory();

 protected:
  // Message Box
  MessageBox m_message_box;

  // std::vector<std::unique_ptr<System>> m_systems;
  TransformSystem m_transform_system;
  MeshSystem m_mesh_system;

  // "Outside" references
  Window& m_window;

  // Resource managers
  MeshManager m_mesh_manager;
  ShaderManager m_shader_manager;
  TextureManager m_texture_manager;
  MaterialManager m_material_manager;

  // Peripherals
  KeyboardInputPeripheral m_keyboard_input_manager;

  // Factory
  GameObjectFactory m_game_object_factory;

  // Rendering
  Renderer3D m_renderer3d;
};
}
#endif  // ENGINE_H
