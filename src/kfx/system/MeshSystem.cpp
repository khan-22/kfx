#include "kfx/system/MeshSystem.h"

#include "kfx/EventListener.h"
#include "kfx/StandardEventMessage.h"

namespace kfx {
MeshSystem::MeshSystem(MessageBox& message_box,
                       TransformSystem& transform_system)
    : m_message_box(message_box), m_transform_system(transform_system) {}

MeshSystem::~MeshSystem() {}

void MeshSystem::addMesh(GameObject game_object, Handle mesh, Handle material) {
  m_single_component_system.addComponentToObject(game_object, glm::mat4(1.f),
                                                 mesh, material);
}

void MeshSystem::removeMesh(GameObject game_object) {
  m_single_component_system.removeComponentFromObject(game_object);
}

Handle MeshSystem::mesh(GameObject game_object) {
  return m_single_component_system.objectToComponent(game_object).mesh;
}

Handle MeshSystem::material(GameObject game_object) {
  return m_single_component_system.objectToComponent(game_object).material;
}

// void MeshSystem::tell(Message& msg) {
//   // if (auto data = std::get_if<UpdatedWorldTransform>(&msg)) {
//   //   m_components[m_object_to_component_index[data->object.index]]
//   //       .world_transform = data->world_transform;
//   // }
// }

void MeshSystem::renderAll() {
  for (auto& dirty_object : m_transform_system.queryDirtyObjects()) {
    if (m_single_component_system.objectHasComponent(dirty_object)) {
      m_single_component_system.objectToComponent(dirty_object)
          .world_transform = m_transform_system.getWorldTransform(dirty_object);
    }
  }

  for (auto& component : m_single_component_system.getComponents()) {
    Message msg = RenderMesh{component.world_transform, component.mesh,
                             component.material};

    m_message_box.postMessage(msg);
  }
}
}
