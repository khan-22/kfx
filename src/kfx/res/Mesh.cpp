#include "kfx/res/Mesh.h"

#include "kfx/Assert.h"

namespace kfx {
Mesh::Mesh(const std::vector<Vertex3D>& vertices,
           const std::vector<GLuint>& indices) {
  kfx_contract(vertices.size() > 0);
  kfx_contract(indices.size() > 0);
  // ...

  vertex_array_object.uploadVertexData(vertices);
  vertex_array_object.uploadIndexData(indices);
}

Mesh::Mesh(Mesh&& other) {
  this->vertex_array_object = std::move(other.vertex_array_object);
}

Mesh::~Mesh() {}

void Mesh::operator=(Mesh&& other) {
  if (this != &other) {
    this->vertex_array_object = std::move(other.vertex_array_object);
  }
}
}
