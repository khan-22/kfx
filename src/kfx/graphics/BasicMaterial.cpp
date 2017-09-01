#include "kfx/graphics/BasicMaterial.h"

#include "kfx/graphics/Shader.h"
#include "kfx/graphics/Texture.h"

namespace kfx {
BasicMaterial::BasicMaterial(ShaderManager& shader_manager,
                             TextureManager& texture_manager)
    : Material(shader_manager, texture_manager) {}

void BasicMaterial::bind() {
  //
  Shader* shader =
      m_shader_manager.getShaders().getResourceEntry(m_basic_shader);

  Texture* texture_diffuse =
      m_texture_manager.getTextures().getResourceEntry(m_texture_diffuse);

  glUseProgram(shader->program);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_diffuse->texture);

  glUniform1i(glGetUniformLocation(shader->program, "u_diffuse"), 0);
}
}
