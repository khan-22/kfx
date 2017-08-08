#include "kfx/resources/MeshUtil.h"

#include <GL/glew.h>

#include <kfx/Assert.h>

namespace kfx {
namespace util {
Mesh meshFromData(const std::vector<Vertex3D>& vertices,
                  const std::vector<GLuint>& indices) {
  // kfx_contract(vertices.size() > 0);
  // kfx_contract(indices.size() > 0);
  // // ...
  // Mesh mesh;
  // //  mesh.vertices = vertices;
  // mesh.draw_count = indices.size();

  // glGenVertexArrays(1, &mesh.vertex_array_object);
  // glBindVertexArray(mesh.vertex_array_object);

  // glEnableVertexAttribArray(0);
  // glEnableVertexAttribArray(1);
  // glEnableVertexAttribArray(2);

  // glGenBuffers(Mesh::NUM_BUFFERS, mesh.vertex_buffer_objects);

  // glBindBuffer(GL_ARRAY_BUFFER,
  //              mesh.vertex_buffer_objects[Mesh::VERTEX_BUFFER]);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(),
  //              vertices.data(), GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
  // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
  //                       (void*)offsetof(Vertex3D, uv));
  // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
  //                       (void*)offsetof(Vertex3D, normal));

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
  //              mesh.vertex_buffer_objects[Mesh::INDEX_BUFFER]);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(),
  //              indices.data(), GL_STATIC_DRAW);

  // glBindVertexArray(0);

  // return mesh;
}
}
}
