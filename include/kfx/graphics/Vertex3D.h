/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef VERTEX_3D_H
#define VERTEX_3D_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace kfx {
struct Vertex3D {
 public:
  glm::vec3 pos;
  glm::vec2 uv;
  glm::vec3 normal;

  static size_t byteSize() { return sizeof(Vertex3D); }
};
}
#endif  // VERTEX_3D_H
