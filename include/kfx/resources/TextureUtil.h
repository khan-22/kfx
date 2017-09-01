/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TEXTURE_UTIL_H
#define TEXTURE_UTIL_H

#include <string>
#include <vector>

#include "kfx/graphics/Image.h"
#include "kfx/graphics/Texture.h"

namespace kfx {
namespace util {
Image loadImage(std::string path);

Texture textureFromImage(const Image& image);
}
}

#endif  // TEXTURE_UTIL_H
