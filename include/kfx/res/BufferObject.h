/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <GL/glew.h>
#include <vector>

namespace kfx {
namespace detail {
template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
class BufferObject {
 public:
  BufferObject();
  BufferObject(BufferObject&& other);
  ~BufferObject();

  void operator=(BufferObject&& other);

  void bind();

  void uploadData(const std::vector<T>& data);

  GLuint getCount() const;

 private:
  // Copying is not allowed
  BufferObject(const BufferObject& other) = delete;
  void operator=(const BufferObject& other) = delete;

  GLuint m_buffer;
  GLuint m_count;
};

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
BufferObject<T, BUFFER_KIND, USAGE>::BufferObject()
    : m_buffer(0U), m_count(0U) {
  glGenBuffers(1, &m_buffer);
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
BufferObject<T, BUFFER_KIND, USAGE>::BufferObject(BufferObject&& other) {
  this->m_buffer = other.m_buffer;
  this->m_count = other.m_count;

  other.m_buffer = 0U;
  other.m_count = 0U;
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
BufferObject<T, BUFFER_KIND, USAGE>::~BufferObject() {
  glDeleteBuffers(1, &m_buffer);
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
void BufferObject<T, BUFFER_KIND, USAGE>::operator=(BufferObject&& other) {
  if (this != &other) {
    this->m_buffer = other.m_buffer;
    this->m_count = other.m_count;

    other.m_buffer = 0U;
    other.m_count = 0U;
  }
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
void BufferObject<T, BUFFER_KIND, USAGE>::bind() {
  glBindBuffer(BUFFER_KIND, m_buffer);
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
void BufferObject<T, BUFFER_KIND, USAGE>::uploadData(
    const std::vector<T>& data) {
  bind();
  glBufferData(BUFFER_KIND, sizeof(T) * data.size(), data.data(), USAGE);
  m_count = data.size();
}

template <typename T, GLenum BUFFER_KIND, GLenum USAGE>
GLuint BufferObject<T, BUFFER_KIND, USAGE>::getCount() const {
  return m_count;
}
}

template <typename T>
using StaticArrayBufferObject =
    detail::BufferObject<T, GL_ARRAY_BUFFER, GL_STATIC_DRAW>;
template <typename T>
using DynamicArrayBufferObject =
    detail::BufferObject<T, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;

template <typename T>
using StaticElementBufferObject =
    detail::BufferObject<T, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>;
template <typename T>
using DynamicElementBufferObject =
    detail::BufferObject<T, GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW>;
}
#endif  // BUFFER_OBJECT_H
