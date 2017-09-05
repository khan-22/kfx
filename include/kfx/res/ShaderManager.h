/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <unordered_map>

#include "kfx/Handle.h"
#include "kfx/res/HandledResource.h"
#include "kfx/res/Shader.h"

#include "kfx/res/FileUtil.h"

namespace kfx {
class ShaderManager final {
 public:
  Handle loadShaderFromFile(const fs::path path);

  Handle getShaderByName(const std::string name);

  HandledResource<Shader>& getShaders();

 private:
  std::unordered_map<std::string, Handle> m_name_to_handle_map;

  HandledResource<Shader> m_shaders;

  const fs::path RESOURCE_PATH = "./res/shaders";
};
}
#endif  // SHADER_MANAGER_H
