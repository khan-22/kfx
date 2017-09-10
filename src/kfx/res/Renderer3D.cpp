#include "kfx/res/Renderer3D.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/Engine.h"

namespace kfx {
Renderer3D::Renderer3D(MessageBox& message_box, Engine& engine)
    : EventListener(message_box), m_engine(engine) {
  //
  m_message_box.registerListener<RenderMesh>(this);
  m_message_box.registerListener<SubmitViewport>(this);
  m_message_box.registerListener<SubmitPointLight>(this);

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
  } else if (auto data = std::get_if<SubmitViewport>(&msg)) {
    m_view_transform = data->view_transform;
  } else if (auto data = std::get_if<SubmitPointLight>(&msg)) {
    PointLight point_light;
    point_light.position = data->position;
    point_light.color = data->color;
    point_light.radius = data->radius;
    m_point_lights.push_back(point_light);
  }
}

void Renderer3D::render() {
  //
  auto& mesh_manager = m_engine.getMeshManager();
  auto& shader_manager = m_engine.getShaderManager();
  auto& texture_manager = m_engine.getTextureManager();
  auto& material_manager = m_engine.getMaterialManager();

  const int MAX_LIGHTS = 4;
  std::vector<glm::vec3> positions(MAX_LIGHTS);
  std::vector<glm::vec4> colors(MAX_LIGHTS);
  // std::vector<float> radiuses(MAX_LIGHTS);

  for (int i = 0; i < m_point_lights.size(); i++) {
    positions[i] = m_point_lights[i].position;
    colors[i] = glm::vec4(m_point_lights[i].color, m_point_lights[i].radius);
    // radiuses[i] = m_point_lights[i].radius;
  }

  for (auto& draw_call : m_draw_calls) {
    Mesh* current_mesh =
        mesh_manager.getMeshes().getResourceEntry(draw_call.mesh);

    Material* current_material =
        material_manager.getMaterials().getResourceEntry(draw_call.material);

    current_material->bind();

    glm::mat4 MVP =
        glm::perspective(glm::pi<float>() / 2.f, 640.f / 480.f, 0.01f, 1000.f) *
        m_view_transform * draw_call.world_transform;

    GLuint M_location = current_material->getLocation("u_M");
    glUniformMatrix4fv(M_location, 1, GL_FALSE,
                       &draw_call.world_transform[0][0]);
    GLuint MVP_location = current_material->getLocation("u_MVP");
    glUniformMatrix4fv(MVP_location, 1, GL_FALSE, &MVP[0][0]);

    std::string prefix = "u_point_lights";
    GLuint position_location =
        current_material->getLocation(prefix + ".position");
    glUniform3fv(position_location, MAX_LIGHTS, &positions[0][0]);

    GLuint color_location = current_material->getLocation(prefix + ".color");
    glUniform4fv(color_location, MAX_LIGHTS, &colors[0][0]);

    // GLuint radius_location = current_material->getLocation(prefix +
    // ".radius");
    // glUniform1fv(radius_location, MAX_LIGHTS, &radiuses[0]);

    glBindVertexArray(current_mesh->vertex_array_object);
    glDrawElements(GL_TRIANGLES, current_mesh->vertex_array_object.getCount(),
                   GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  m_draw_calls.clear();
  m_point_lights.clear();
}
}
