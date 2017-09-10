/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/res/Vertex3D.h"

#include "kfx/res/VertexArrayObject.h"

namespace kfx {
struct Mesh {
  Mesh(const std::vector<Vertex3D>& vertices,
       const std::vector<GLuint>& indices);
  Mesh(Mesh&& other);
  ~Mesh();

  void operator=(Mesh&& other);

  StaticVertexArrayObject vertex_array_object;

 private:
  // Copying is not allowed
  Mesh(const Mesh& other) = delete;
  void operator=(const Mesh& other) = delete;
};
}
#endif  // MESH_H
