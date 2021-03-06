#include "kfx/graphics/Renderer3D.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/Engine.h"

namespace kfx {
Renderer3D::Renderer3D(MessageBox& message_box, Engine& engine)
    : EventListener(message_box), m_engine(engine) {
  //
  m_message_box.registerListener<RenderMesh>(this);

  glEnable(GL_DEPTH_TEST);
}

Renderer3D::~Renderer3D() {
  //
  m_message_box.unregisterListener(this);
}

void Renderer3D::tell(Message& msg) {
  if (auto data = std::get_if<RenderMesh>(&msg)) {
    DrawCall draw_call;
    draw_call.world_transform = data->world_transform;
    draw_call.mesh = data->mesh;
    draw_call.material = data->material;
    m_draw_calls.push_back(draw_call);
  }
}

void Renderer3D::render() {
  //
  auto& mesh_manager = m_engine.getMeshManager();
  auto& shader_manager = m_engine.getShaderManager();
  auto& texture_manager = m_engine.getTextureManager();
  auto& material_manager = m_engine.getMaterialManager();

  for (auto& draw_call : m_draw_calls) {
    //
    // Shader* current_shader =
    //     shader_manager.getShaders().getResourceEntry(draw_call.shader);

    Mesh* current_mesh =
        mesh_manager.getMeshes().getResourceEntry(draw_call.mesh);

    // Texture* current_texture =
    //     texture_manager.getTextures().getResourceEntry(draw_call.texture);

    // glUseProgram(current_shader->program);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, current_texture->texture);
    // glUniform1i(glGetUniformLocation(current_shader->program, "u_diffuse"),
    // 0);
    Material* current_material =
        material_manager.getMaterials().getResourceEntry(draw_call.material);

    current_material->bind();

    glm::mat4 MVP =
        glm::perspective(glm::pi<float>() / 2.f, 640.f / 640.f, 0.01f, 1000.f) *
        glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0, 0, 0),
                    glm::vec3(0.f, 1.f, 0.f)) *
        draw_call.world_transform;

    GLuint MVP_location = current_material->getLocation("u_MVP");
    glUniformMatrix4fv(MVP_location, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(current_mesh->vertex_array_object);
    glDrawElements(GL_TRIANGLES, current_mesh->draw_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_draw_calls.clear();
  }

  /*MVP = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0, 0, 0),
                      glm::vec3(0.f, 1.f, 0.f)) *
          MVP;

    MVP =
        glm::perspective(glm::pi<float>() / 2.f, 640.f / 640.f, 0.01f, 1000.f) *
        MVP;

    glUseProgram(shader->program);
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "u_MVP"), 1,
                       GL_FALSE, &MVP[0][0]);

    glBindVertexArray(mesh->vertex_array_object);
    // glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
    glDrawElements(GL_TRIANGLES, mesh->draw_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);*/
}
}
