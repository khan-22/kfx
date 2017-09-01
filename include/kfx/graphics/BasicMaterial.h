/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef BASIC_MATERIAL_H
#define BASIC_MATERIAL_H

#include "kfx/Handle.h"
#include "kfx/graphics/Material.h"

namespace kfx {
class BasicMaterial final : public Material {
 public:
  BasicMaterial(ShaderManager& shader_manager, TextureManager& texture_manager);
  virtual ~BasicMaterial() final override = default;

  void bind() final override;

 private:
  Handle m_basic_shader;

  Handle m_texture_diffuse;
};
}
#endif  // BASIC_MATERIAL_H
