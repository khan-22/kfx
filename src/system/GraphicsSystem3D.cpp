#include "kfx/system/GraphicsSystem3D.h"

// TEMPORARY!!
#include <GL/glew.h>
#include <iostream>

namespace kfx {
GraphicsSystem3D::GraphicsSystem3D(GameObjectFactory& game_object_factory,
                                   MeshManager& mesh_manager)
    : System(game_object_factory), m_mesh_manager(mesh_manager) {
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

  for (auto& object : game_objects.resource) {
    //std::cout << "Object has component? ["
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
    Mesh* mesh = 
        meshes.getResourceEntry(mesh_component->mesh_handle);

    glBindVertexArray(mesh->vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
    glBindVertexArray(0);
  }
}
}
