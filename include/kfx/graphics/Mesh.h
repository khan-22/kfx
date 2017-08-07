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
  enum { VERTEX_BUFFER, INDEX_BUFFER, NUM_BUFFERS };

  std::vector<Vertex3D> vertices;

  GLuint draw_count;

  GLuint vertex_array_object;
  GLuint vertex_buffer_objects[NUM_BUFFERS];
};
}
#endif  // MESH_H
