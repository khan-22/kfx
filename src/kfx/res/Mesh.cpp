#include "kfx/res/Mesh.h"

#include "kfx/Assert.h"

namespace kfx {
Mesh::Mesh(const std::vector<Vertex3D>& vertices,
           const std::vector<GLuint>& indices)
    : draw_count(0), vertex_array_object(0), vertex_buffer_objects{} {
  //...

  kfx_contract(vertices.size() > 0);
  kfx_contract(indices.size() > 0);
  // ...

  this->draw_count = indices.size();

  glGenVertexArrays(1, &this->vertex_array_object);
  glBindVertexArray(this->vertex_array_object);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glGenBuffers(Mesh::NUM_BUFFERS, this->vertex_buffer_objects);

  glBindBuffer(GL_ARRAY_BUFFER,
               this->vertex_buffer_objects[Mesh::VERTEX_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, uv));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D),
                        (void*)offsetof(Vertex3D, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
               this->vertex_buffer_objects[Mesh::INDEX_BUFFER]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(),
               indices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other)
    : draw_count(0), vertex_array_object(0), vertex_buffer_objects{} {
  //...
  this->draw_count = std::move(other.draw_count);
  this->vertex_array_object = std::move(other.vertex_array_object);
  for (unsigned int i = 0; i < Mesh::NUM_BUFFERS; i++) {
    this->vertex_buffer_objects[i] = std::move(other.vertex_buffer_objects[i]);
  }

  other.draw_count = 0;
  other.vertex_array_object = 0;
  for (unsigned int i = 0; i < Mesh::NUM_BUFFERS; i++) {
    other.vertex_buffer_objects[i] = 0;
  }
}

Mesh::~Mesh() {
  //...
  glDeleteVertexArrays(1, &vertex_array_object);
  glDeleteBuffers(Mesh::NUM_BUFFERS, vertex_buffer_objects);

  this->draw_count = 0;
  this->vertex_array_object = 0;
  for (unsigned int i = 0; i < Mesh::NUM_BUFFERS; i++) {
    this->vertex_buffer_objects[i] = 0;
  }
}

void Mesh::operator=(Mesh&& other) {
  if (this != &other) {
    this->draw_count = std::move(other.draw_count);
    this->vertex_array_object = std::move(other.vertex_array_object);
    for (unsigned int i = 0; i < Mesh::NUM_BUFFERS; i++) {
      this->vertex_buffer_objects[i] =
          std::move(other.vertex_buffer_objects[i]);
    }

    other.draw_count = 0;
    other.vertex_array_object = 0;
    for (unsigned int i = 0; i < Mesh::NUM_BUFFERS; i++) {
      other.vertex_buffer_objects[i] = 0;
    }
  }
}
}
