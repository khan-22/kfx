
#include "kfx/resources/ShaderManager.h"

#include "kfx/resources/FileUtil.h"
#include "kfx/resources/ShaderUtil.h"

namespace kfx {
Handle ShaderManager::loadShaderFromFile(const std::string path) {
  std::string shader_name = util::breakDownPath(path).back();

  std::string vertex_shader_path = path + "/" + shader_name + ".vs";
  std::string geometry_shader_path = path + "/" + shader_name + ".gs";
  std::string fragment_shader_path = path + "/" + shader_name + ".fs";

  std::string vertex_shader_source =
      util::loadFileIntoStream(vertex_shader_path).str();
  std::string geometry_shader_source =
      util::loadFileIntoStream(geometry_shader_path).str();
  std::string fragment_shader_source =
      util::loadFileIntoStream(fragment_shader_path).str();

  GLuint vertex_shader =
      util::shaderStageFromData(vertex_shader_source, GL_VERTEX_SHADER);
  GLuint geometry_shader =
      util::shaderStageFromData(geometry_shader_source, GL_GEOMETRY_SHADER);
  GLuint fragment_shader =
      util::shaderStageFromData(fragment_shader_source, GL_FRAGMENT_SHADER);

  Handle shader_handle = m_shaders.addResourceEntry();
  Shader* shader = m_shaders.getResourceEntry(shader_handle);
  *shader = util::shaderProgramFromStages(vertex_shader, geometry_shader,
                                          fragment_shader);

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
