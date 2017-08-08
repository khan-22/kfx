/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/graphics/Vertex3D.h"

namespace kfx {
struct Mesh {
  Mesh(const std::vector<Vertex3D>& vertices,
       const std::vector<GLuint>& indices);
  Mesh(Mesh&& other);
  ~Mesh();

  void operator=(Mesh&& other);

  enum { VERTEX_BUFFER, INDEX_BUFFER, NUM_BUFFERS };
  // std::vector<Vertex3D> vertices;

  GLuint draw_count;

  GLuint vertex_array_object;
  GLuint vertex_buffer_objects[NUM_BUFFERS];

 private:
  // Copying is not allowed
  Mesh(const Mesh& other) = delete;
  void operator=(const Mesh& other) = delete;
};
}
#endif  // MESH_H
