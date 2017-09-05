/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include <array>

#include "kfx/Handle.h"
#include "kfx/res/ShaderManager.h"
#include "kfx/res/TextureManager.h"

namespace kfx {
class Material {
 public:
  Material(ShaderManager& shader_manager, TextureManager& texture_manager);
  ~Material() = default;

  void init();
  void bind();

  void setTexture(unsigned int unit, Handle handle);
  void setShader(Handle handle);

  GLuint getLocation(const char* name);

 protected:
  ShaderManager& m_shader_manager;
  TextureManager& m_texture_manager;

  unsigned int m_bound_textures;
  static const int MAX_TEXTURES = 8;
  std::array<Handle, MAX_TEXTURES> m_texture_handles;

  Handle m_shader_handle;
};
}
#endif  // MATERIAL_H
