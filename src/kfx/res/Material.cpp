#include "kfx/res/Material.h"

#include "kfx/Assert.h"

namespace kfx {
Material::Material(ShaderManager& shader_manager,
                   TextureManager& texture_manager)
    : m_shader_manager(shader_manager),
      m_texture_manager(texture_manager),
      m_bound_textures(0){
          //
      };

void Material::init() {
  //
}

void Material::bind() {
  glUseProgram(
      m_shader_manager.getShaders().getResourceEntry(m_shader_handle)->program);

  for (int i = 0; i < m_bound_textures; i++) {
    glActiveTexture(GL_TEXTURE0 + i);

    glBindTexture(GL_TEXTURE_2D,
                  m_texture_manager.getTextures()
                      .getResourceEntry(m_texture_handles[i])
                      ->texture);
  }
}

void Material::setTexture(unsigned int unit, Handle handle) {
  kfx_assert(unit < MAX_TEXTURES);
  m_texture_handles[unit] = handle;

  if ((unit + 1) > m_bound_textures) {
    m_bound_textures = unit + 1;
  }
}

void Material::setShader(Handle handle) { m_shader_handle = handle; }

GLuint Material::getLocation(const char* name) {
  return glGetUniformLocation(
      m_shader_manager.getShaders().getResourceEntry(m_shader_handle)->program,
      name);
}
}
