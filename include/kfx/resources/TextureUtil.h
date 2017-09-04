/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TEXTURE_UTIL_H
#define TEXTURE_UTIL_H

#include <string>
#include <vector>

#include <optional>

#include "kfx/graphics/Image.h"
#include "kfx/graphics/Texture.h"

#include "kfx/resources/FileUtil.h"

namespace kfx {
namespace util {
std::optional<Image> loadImage(fs::path path);
}
}

#endif  // TEXTURE_UTIL_H
