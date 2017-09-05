/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/res/HandledResource.h"
#include "kfx/res/Material.h"
#include "kfx/res/MaterialParser.h"

#include "kfx/res/ShaderManager.h"
#include "kfx/res/TextureManager.h"

#include "kfx/res/FileUtil.h"

namespace kfx {
class MaterialManager {
 public:
  MaterialManager(ShaderManager& shader_manager,
                  TextureManager& texture_manager);

  Handle loadMaterialFromFile(const fs::path path);
  Handle loadMaterialFromMemory(const std::string name,
                                const std::string description);

  Handle getMaterialByName(const std::string name);

  HandledResource<Material>& getMaterials();

 private:
  std::unordered_map<std::string, Handle> m_name_to_handle_map;

  HandledResource<Material> m_materials;

  MaterialParser m_material_parser;

  ShaderManager& m_shader_manager;
  TextureManager& m_texture_manager;

  const fs::path RESOURCE_PATH = "./res/materials";
};
}
#endif  // MATERIAL_MANAGER_H
