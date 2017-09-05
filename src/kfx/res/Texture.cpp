#include "kfx/res/Texture.h"

namespace kfx {

Texture::Texture(const Image& image)
    : width(image.width), height(image.height) {
  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_2D, this->texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
  //                 GL_LINEAR_MIPMAP_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glGenerateMipmap(GL_TEXTURE_2D);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image.data.data());

  // Unbind
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& other) : width(0), height(0) {
  this->width = std::move(other.width);
  this->height = std::move(other.height);
  this->texture = std::move(other.texture);

  other.width = 0;
  other.height = 0;
  other.texture = 0;
}

Texture::~Texture() {
  glDeleteTextures(1, &this->texture);
  this->width = 0;
  this->height = 0;
  this->texture = 0;
}

void Texture::operator=(Texture&& other) {
  if (this != &other) {
    this->width = std::move(other.width);
    this->height = std::move(other.height);
    this->texture = std::move(other.texture);

    other.width = 0;
    other.height = 0;
    other.texture = 0;
  }
}
}
