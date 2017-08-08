#include "kfx/resources/TextureUtil.h"

#include <GL/glew.h>
#include <lodepng/lodepng.h>

#include "kfx/Assert.h"

namespace kfx {
namespace util {
Image loadImage(std::string path) {
  Image image;

  std::string file_path = path + ".png";

  unsigned error =
      lodepng::decode(image.data, image.width, image.height, file_path.c_str());

  kfx_contract(error == 0);

  return image;
}

Texture textureFromImage(const Image& image) {
  Texture texture;

  texture.width = image.width;
  texture.height = image.height;

  glGenTextures(1, &texture.texture);
  glBindTexture(GL_TEXTURE_2D, texture.texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  //                 GL_LINEAR_MIPMAP_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glGenerateMipmap(GL_TEXTURE_2D);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, image.data.data());

  // Unbind
  glBindTexture(GL_TEXTURE_2D, 0);

  return texture;
}
}
}
