/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace kfx {
struct Texture {
  GLuint texture;

  uint32_t width;
  uint32_t height;
};
}
#endif  // TEXTURE_H
