/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/HandleManager.h"
#include "kfx/res/Image.h"
#include "kfx/res/Texture.h"

#include "kfx/res/HandledResource.h"

#include "kfx/res/FileUtil.h"

namespace kfx {
class TextureManager final {
 public:
  Handle loadTextureFromFile(const fs::path path);

  Handle getTextureByName(const std::string name);

  HandledResource<Texture>& getTextures();

 private:
  std::unordered_map<std::string, Handle> m_name_to_handle_map;

  HandledResource<Texture> m_textures;

  const fs::path RESOURCE_PATH = "./res/textures";
};
}
#endif  // TEXTURE_MANAGER_H
