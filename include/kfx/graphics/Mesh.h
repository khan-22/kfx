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
 public:
  Handle handle;

  std::vector<Vertex3D> vertices;

  GLuint vertex_array_object;
  GLuint vertex_buffer_object;
};
}
#endif  // MESH_H
