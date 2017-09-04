
#include "kfx/resources/ShaderManager.h"

#include "kfx/resources/FileUtil.h"
#include "kfx/resources/ShaderUtil.h"

namespace kfx {
Handle ShaderManager::loadShaderFromFile(const fs::path path) {
  std::string shader_name = path.filename();

  Handle found_handle = getShaderByName(shader_name);
  if (found_handle != Handle::NULL_HANDLE) {
    return found_handle;
  }

  fs::path vert_shader_path = RESOURCE_PATH / path / (shader_name + ".vs");
  fs::path geom_shader_path = RESOURCE_PATH / path / (shader_name + ".gs");
  fs::path frag_shader_path = RESOURCE_PATH / path / (shader_name + ".fs");

  std::string vert_shader_source =
      util::loadFileIntoStream(vert_shader_path).str();
  std::string geom_shader_source =
      util::loadFileIntoStream(geom_shader_path).str();
  std::string frag_shader_source =
      util::loadFileIntoStream(frag_shader_path).str();

  GLuint vert_shader =
      util::shaderStageFromData(vert_shader_source, GL_VERTEX_SHADER);
  GLuint geom_shader =
      util::shaderStageFromData(geom_shader_source, GL_GEOMETRY_SHADER);
  GLuint frag_shader =
      util::shaderStageFromData(frag_shader_source, GL_FRAGMENT_SHADER);

  Handle shader_handle =
      m_shaders.addResourceEntry(vert_shader, geom_shader, frag_shader);
  // Shader* shader = m_shaders.getResourceEntry(shader_handle);
  //*shader = util::shaderProgramFromStages(vertex_shader, geometry_shader,
  //                                        fragment_shader);

  m_name_to_handle_map[shader_name] = shader_handle;

  return shader_handle;
}

Handle ShaderManager::getShaderByName(const std::string name) {
  auto it = m_name_to_handle_map.find(name);
  if (it != m_name_to_handle_map.end()) {
    return it->second;
  } else {
    return Handle::NULL_HANDLE;
  }
}

HandledResource<Shader>& ShaderManager::getShaders() { return m_shaders; }
}
