/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <unordered_map>

#include "kfx/Handle.h"
#include "kfx/graphics/Shader.h"
#include "kfx/resources/HandledResource.h"

namespace kfx {
class ShaderManager final {
 public:
  Handle loadShaderFromFile(const std::string path);

  Handle getShaderByName(const std::string name);

  HandledResource<Shader>& getShaders();

 private:
  std::unordered_map<std::string, Handle> m_name_to_handle_map;

  HandledResource<Shader> m_shaders;
};
}
#endif  // SHADER_MANAGER_H
