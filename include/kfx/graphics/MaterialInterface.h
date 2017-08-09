/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MATERIAL_INTERFACE_H
#define MATERIAL_INTERFACE_H

#include "kfx/resources/ShaderManager.h"
#include "kfx/resources/TextureManager.h"

namespace kfx {
class MaterialInterface {
 public:
  MaterialInterface(ShaderManager& shader_manager,
                    TextureManager& texture_manager)
      : m_shader_manager(shader_manager), m_texture_manager(texture_manager){};
  virtual ~MaterialInterface() = default;

  virtual void bind() = 0;

 protected:
  ShaderManager& m_shader_manager;
  TextureManager& m_texture_manager;
};
}
#endif  // MATERIAL_INTERFACE_H
