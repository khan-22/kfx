#include "kfx/res/MaterialManager.h"

#include <sstream>

#include "kfx/res/FileUtil.h"

namespace kfx {

MaterialManager::MaterialManager(ShaderManager& shader_manager,
                                 TextureManager& texture_manager)
    : m_shader_manager(shader_manager), m_texture_manager(texture_manager) {}

Handle MaterialManager::loadMaterialFromFile(const fs::path path) {
  std::string material_name = path.filename();

  Handle found_handle = getMaterialByName(material_name);
  if (found_handle != Handle::NULL_HANDLE) {
    return found_handle;
  }

  fs::path extended_path = RESOURCE_PATH / path;
  extended_path += ".mat";

  // May be inefficient... Reconsider?
  std::istringstream stream(util::loadFileIntoStream(extended_path).str());
  std::optional<MaterialParser::Fields> result =
      m_material_parser.parse(stream);
  if (!result) {
    return Handle::NULL_HANDLE;
  }

  Handle material_handle =
      m_materials.addResourceEntry(m_shader_manager, m_texture_manager);

  if (material_handle == Handle::NULL_HANDLE) {
    return Handle::NULL_HANDLE;
  }

  Material* material = m_materials.getResourceEntry(material_handle);

  if (result->getType() == "Basic") {
    material->setShader(m_shader_manager.loadShaderFromFile("basic"));

    Handle diffuse_handle = Handle::NULL_HANDLE;
    std::string diffuse_file;
    if (result->find("$Diffuse", diffuse_file)) {
      diffuse_handle = m_texture_manager.loadTextureFromFile(diffuse_file);
    }
    material->setTexture(0, diffuse_handle);

    // std::string normal_file;
    // if (fields.find("$Diffuse", normal_file)) {
    //   normal_handle = m_texture_manager.loadTextureFromFile(normal_file);
    // } else {
    //   normal_handle = m_texture_manager.loadTextureFromFile(
    //       "./res/textures/missing_texture.png");
    // }
  }

  m_name_to_handle_map[material_name] = material_handle;

  return material_handle;
}

Handle MaterialManager::loadMaterialFromMemory(const std::string name,
                                               const std::string description) {
  //
}

Handle MaterialManager::getMaterialByName(const std::string name) {
  auto it = m_name_to_handle_map.find(name);
  if (it != m_name_to_handle_map.end()) {
    return it->second;
  } else {
    return Handle::NULL_HANDLE;
  }
}

HandledResource<Material>& MaterialManager::getMaterials() {
  return m_materials;
}
}
