/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <GL/glew.h>
#include <vector>

#include "kfx/res/BufferObject.h"
#include "kfx/res/Vertex3D.h"

namespace kfx {
namespace detail {

template <GLenum USAGE>
class VertexArrayObject {
 public:
  VertexArrayObject();
  VertexArrayObject(VertexArrayObject&& other);
  ~VertexArrayObject();

  void operator=(VertexArrayObject&& other);
  operator GLuint();

  void bind();
  void unbind();

  void uploadVertexData(const std::vector<Vertex3D>& vertex_data);
  void uploadIndexData(const std::vector<GLuint>& index_data);

  GLuint getCount() const;

 private:
  // Copying is not allowed
  VertexArrayObject(const VertexArrayObject& other) = delete;
  void operator=(const VertexArrayObject& other) = delete;

  GLuint m_vao;

  detail::BufferObject<Vertex3D, GL_ARRAY_BUFFER, USAGE> m_vertex_buffer;
  detail::BufferObject<GLuint, GL_ELEMENT_ARRAY_BUFFER, USAGE> m_index_buffer;
};

template <GLenum USAGE>
VertexArrayObject<USAGE>::VertexArrayObject() : m_vao(0U) {
  glGenVertexArrays(1, &m_vao);

  bind();
  m_vertex_buffer.bind();
  m_index_buffer.bind();

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, uv));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, normal));

  unbind();
}

template <GLenum USAGE>
VertexArrayObject<USAGE>::VertexArrayObject(VertexArrayObject&& other) {
  this->m_vao = other.m_vao;

  this->m_vertex_buffer = std::move(other.m_vertex_buffer);
  this->m_index_buffer = std::move(other.m_index_buffer);

  other.m_vao = 0U;
}

template <GLenum USAGE>
VertexArrayObject<USAGE>::~VertexArrayObject() {
  glDeleteVertexArrays(1, &m_vao);
}

template <GLenum USAGE>
void VertexArrayObject<USAGE>::operator=(VertexArrayObject&& other) {
  if (this != &other) {
    this->m_vao = other.m_vao;

    this->m_vertex_buffer = std::move(other.m_vertex_buffer);
    this->m_index_buffer = std::move(other.m_index_buffer);

    other.m_vao = 0U;
  }
}

template <GLenum USAGE>
VertexArrayObject<USAGE>::operator GLuint() {
  return m_vao;
}

template <GLenum USAGE>
void VertexArrayObject<USAGE>::bind() {
  glBindVertexArray(m_vao);
}

template <GLenum USAGE>
void VertexArrayObject<USAGE>::unbind() {
  glBindVertexArray(0);
}

template <GLenum USAGE>
void VertexArrayObject<USAGE>::uploadVertexData(
    const std::vector<Vertex3D>& vertex_data) {
  bind();
  m_vertex_buffer.uploadData(vertex_data);
  unbind();
}

template <GLenum USAGE>
void VertexArrayObject<USAGE>::uploadIndexData(
    const std::vector<GLuint>& index_data) {
  bind();
  m_index_buffer.uploadData(index_data);
  unbind();
}

template <GLenum USAGE>
GLuint VertexArrayObject<USAGE>::getCount() const {
  return m_index_buffer.getCount();
}
}

using StaticVertexArrayObject = detail::VertexArrayObject<GL_STATIC_DRAW>;
using DynamicVertexArrayObject = detail::VertexArrayObject<GL_DYNAMIC_DRAW>;
}
#endif  // VERTEX_ARRAY_OBJECT_H
