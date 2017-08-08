#include "kfx/resources/TextureManager.h"

#include "kfx/resources/FileUtil.h"
#include "kfx/resources/TextureUtil.h"

namespace kfx {
Handle TextureManager::loadTextureFromFile(const std::string path) {
  std::string texture_name = util::breakDownPath(path).back();

  // If the texture has already been loaded, return the handle
  Handle found_handle = getTextureByName(texture_name);
  if (found_handle != Handle::NULL_HANDLE) {
    return found_handle;
  }

  Image image = util::loadImage(path);
  Handle texture_handle = m_textures.addResourceEntry(image);
  if (texture_handle == Handle::NULL_HANDLE) {
    return Handle::NULL_HANDLE;
  }

  // Texture* texture = m_textures.getResourceEntry(texture_handle);
  // *texture = util::textureFromImage(image);

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
