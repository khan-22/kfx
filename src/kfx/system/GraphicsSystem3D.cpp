#include "kfx/system/GraphicsSystem3D.h"

#include "kfx/Assert.h"
#include "kfx/Engine.h"

// TEMPORARY!!
#include <GL/glew.h>
#include <iostream>

namespace kfx {
GraphicsSystem3D::GraphicsSystem3D(MessageBox& message_box, Engine* engine)
    : System(engine), EventListener(message_box), m_total_time(0.f) {
  // ...

  m_message_box.registerListener<KeyAction>(this);
}

GraphicsSystem3D::~GraphicsSystem3D() {
  // ...

  m_message_box.unregisterListener(this);
}

void GraphicsSystem3D::update(float dt) {
  // GameObjectFactory& game_object_factory = m_engine->getGameObjectFactory();

  // HandledResource<GameObject>& game_objects =
  //     game_object_factory.getGameObjects();

  // // HandleManager& mesh_handle_manager = m_mesh_manager.getHandleManager();
  // HandledResource<Mesh>& meshes = m_engine->getMeshManager().getMeshes();

  // HandledResource<Shader>& shaders =
  // m_engine->getShaderManager().getShaders();

  // for (auto& object : game_objects.resource) {
  //   // std::cout << "Object has component? ["
  //   //          << (object.value.hasComponent(ComponentType::MESH) ? "YES]"
  //   //                                                             : "NO]")
  //   //          << std::endl;

  //   TransformComponent* transform_component =
  //       game_object_factory.getTransformComponents().getResourceEntry(
  //           object.value.getComponent(ComponentType::TRANSFORM));

  //   // transform_component->pos.x += 0.01f;
  //   // std::cout << "X: " << transform_component->pos.x << std::endl;

  //   MeshComponent* mesh_component =
  //       game_object_factory.getMeshComponents().getResourceEntry(
  //           object.value.getComponent(ComponentType::MESH));

  //   // Mesh* mesh = static_cast<Mesh*>(
  //   //     mesh_handle_manager.getEntry(mesh_component->mesh_handle));
  //   // Mesh* mesh = meshes.getResourceEntry(mesh_component->mesh_handle);
  //   // Shader* shader =
  //   shaders.getResourceEntry(mesh_component->shader_handle);

  //   m_total_time += 6.28f * dt;
  //   glm::vec3 point_at =
  //       glm::vec3(sinf(m_total_time) * 2.f, 0.f, cosf(m_total_time) * 2.f);

  //   transform_component->setPosition(glm::vec3(
  //       sinf(m_total_time / 3.f) * 4.f, 0.f, cosf(m_total_time / 3.f) *
  //       4.f));
  //   transform_component->lookAt(point_at, glm::vec3(0.f, 1.f, 0.f));
  //   // glm::mat4 MVP = transform_component->getModel();

  //   MessageArgument arg;
  //   arg.init<StandardEventMessage::RENDER_MESH>();
  //   auto* data = arg.getDataPointer<StandardEventMessage::RENDER_MESH>();

  //   data->world_transform = transform_component->getModel();
  //   data->mesh = mesh_component->mesh_handle;
  //   data->material = mesh_component->material_handle;
  //   // data->shader = mesh_component->shader_handle;
  //   // data->texture = mesh_component->texture_handle;

  //   m_message_box.postMessage(arg);

  //   // MVP = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0, 0, 0),
  //   //                   glm::vec3(0.f, 1.f, 0.f)) *
  //   //       MVP;

  //   // MVP =
  //   //     glm::perspective(glm::pi<float>() / 2.f, 640.f / 640.f, 0.01f,
  //   //     1000.f) *
  //   //     MVP;

  //   // glUseProgram(shader->program);
  //   // glUniformMatrix4fv(glGetUniformLocation(shader->program, "u_MVP"), 1,
  //   //                    GL_FALSE, &MVP[0][0]);

  //   // glBindVertexArray(mesh->vertex_array_object);
  //   // // glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
  //   // glDrawElements(GL_TRIANGLES, mesh->draw_count, GL_UNSIGNED_INT, 0);
  //   // glBindVertexArray(0);
  // }
}

void GraphicsSystem3D::tell(Message& msg) {
  if (auto data = std::get_if<KeyAction>(&msg)) {
    switch (data->action) {
      case GLFW_PRESS: {
        m_total_time = 0.f;
        break;
      }
    }
  }
}
}
