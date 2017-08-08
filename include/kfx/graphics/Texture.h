/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include "kfx/graphics/Image.h"

namespace kfx {
struct Texture {
  Texture(const Image& image);
  Texture(Texture&& other);
  ~Texture();

  void operator=(Texture&& other);

  GLuint texture;

  uint32_t width;
  uint32_t height;

 private:
  // No copying allowed
  Texture(const Texture& other) = delete;
  void operator=(const Texture& other) = delete;
};
}
#endif  // TEXTURE_H
