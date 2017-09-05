#include "kfx/res/TextureManager.h"

#include "kfx/res/FileUtil.h"
#include "kfx/res/TextureUtil.h"

namespace kfx {
Handle TextureManager::loadTextureFromFile(const fs::path path) {
  std::string texture_name = path.filename();

  // If the texture has already been loaded, return the handle
  Handle found_handle = getTextureByName(texture_name);
  if (found_handle != Handle::NULL_HANDLE) {
    return found_handle;
  }

  fs::path extended_path = RESOURCE_PATH / path;
  extended_path += ".png";

  std::optional<Image> image = util::loadImage(extended_path);
  if (!image) {
    return Handle::NULL_HANDLE;
  }

  Handle texture_handle = m_textures.addResourceEntry(*image);
  if (texture_handle == Handle::NULL_HANDLE) {
    return Handle::NULL_HANDLE;
  }

  m_name_to_handle_map[texture_name] = texture_handle;

  return texture_handle;
}

Handle TextureManager::getTextureByName(const std::string name) {
  auto it = m_name_to_handle_map.find(name);
  if (it != m_name_to_handle_map.end()) {
    return it->second;
  } else {
    return Handle::NULL_HANDLE;
  }
}

HandledResource<Texture>& TextureManager::getTextures() { return m_textures; }
}
