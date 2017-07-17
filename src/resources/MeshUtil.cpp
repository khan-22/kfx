#include "kfx/resources/MeshUtil.h"

namespace kfx {
namespace util {
Mesh meshFromData(const std::vector<Vertex3D>& vertices) {
  // ...
  Mesh mesh;
  mesh.vertices = vertices;

  glGenVertexArrays(1, &mesh.vertex_array_object);
  glBindVertexArray(mesh.vertex_array_object);

  glEnableVertexAttribArray(0);

  glGenBuffers(1, &mesh.vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices[0]) * mesh.vertices.size(),
               mesh.vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);

  glBindVertexArray(0);

  return mesh;
}
}
}
