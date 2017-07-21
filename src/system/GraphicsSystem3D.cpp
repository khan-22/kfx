#include "kfx/system/GraphicsSystem3D.h"

// TEMPORARY!!
#include <GL/glew.h>
#include <iostream>

namespace kfx {
GraphicsSystem3D::GraphicsSystem3D(GameObjectFactory& game_object_factory,
                                   MeshManager& mesh_manager,
                                   ShaderManager& shader_manager)
    : System(game_object_factory),
      m_mesh_manager(mesh_manager),
      m_shader_manager(shader_manager) {
  // ...
}

GraphicsSystem3D::~GraphicsSystem3D() {
  // ...
}

void GraphicsSystem3D::update(float dt) {
  HandledResource<GameObject>& game_objects =
      m_game_object_factory.getGameObjects();

  // HandleManager& mesh_handle_manager = m_mesh_manager.getHandleManager();
  HandledResource<Mesh>& meshes = m_mesh_manager.getMeshes();

  HandledResource<Shader>& shaders = m_shader_manager.getShaders();

  for (auto& object : game_objects.resource) {
    // std::cout << "Object has component? ["
    //          << (object.value.hasComponent(ComponentType::MESH) ? "YES]"
    //                                                             : "NO]")
    //          << std::endl;

    TransformComponent* transform_component =
        m_game_object_factory.getTransformComponents().getResourceEntry(
            object.value.getComponent(ComponentType::TRANSFORM));

    // transform_component->pos.x += 0.01f;
    // std::cout << "X: " << transform_component->pos.x << std::endl;

    MeshComponent* mesh_component =
        m_game_object_factory.getMeshComponents().getResourceEntry(
            object.value.getComponent(ComponentType::MESH));

    // Mesh* mesh = static_cast<Mesh*>(
    //     mesh_handle_manager.getEntry(mesh_component->mesh_handle));
    Mesh* mesh = meshes.getResourceEntry(mesh_component->mesh_handle);
    Shader* shader = shaders.getResourceEntry(mesh_component->shader_handle);

    static float total_time = 0.f;
    total_time += 0.05f;
    // glm::vec3 point_at =
    //     glm::vec3(sinf(total_time) * 2.f, sinf(total_time / 4.f) * 2.f,
    //               cosf(total_time) * 2.f);
    glm::vec3 point_at =
        glm::vec3(0.f, sinf(total_time) * 2.f, cosf(total_time) * 2.f);

    transform_component->setPosition(glm::vec3(-5.f, 0.f, 0.f));
    transform_component->lookAt(point_at, glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 MVP = transform_component->getModel();

    // glm::mat4 MVP = glm::mat4(1.f);
    // glm::mat4 T = glm::translate(glm::vec3(0.0f, 0.f, -1.f));
    // glm::mat4 R =
    // glm::rotate(glm::pi<float>() / 2.f, glm::vec3(0.f, 0.f, -1.f));
    // MVP = glm::translate(MVP, glm::vec3(0.0f, 0.f, -1.f));
    // MVP = glm::rotate(MVP, glm::pi<float>() / 2.f, glm::vec3(0.f, 0.f,
    // -1.f));

    // MVP = T * MVP;

    MVP = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0, 0, 0),
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
    glBindVertexArray(0);
  }
}
}
