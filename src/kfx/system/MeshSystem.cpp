#include "kfx/system/MeshSystem.h"

#include "kfx/EventListener.h"
#include "kfx/StandardEventMessage.h"

namespace kfx {
MeshSystem::MeshSystem(MessageBox& message_box) : EventListener(message_box) {
  m_message_box.registerListener(this,
                                 StandardEventMessage::UPDATED_WORLD_TRANSFORM);
}

MeshSystem::~MeshSystem() { m_message_box.unregisterListener(this); }

void MeshSystem::addMesh(GameObject game_object, Handle mesh, Handle material) {
  MeshComponent new_component;
  new_component.object = game_object;
  new_component.world_transform = glm::mat4(1.f);
  new_component.mesh = mesh;
  new_component.material = material;

  m_components.push_back(new_component);

  if (m_object_to_component_index.size() < game_object.index + 1) {
    m_object_to_component_index.resize(game_object.index + 1);
  }

  m_object_to_component_index[game_object.index] = m_components.size() - 1;
}

void MeshSystem::removeMesh(GameObject game_object) {
  MeshComponent& this_component =
      m_components[m_object_to_component_index[game_object.index]];
  MeshComponent& last_component = m_components.back();

  this_component = last_component;
  m_components.pop_back();

  GameObject last_object = last_component.object;
  m_object_to_component_index[last_object.index] =
      m_object_to_component_index[game_object.index];

  m_object_to_component_index[game_object.index] = 0;
}

Handle MeshSystem::mesh(GameObject game_object) {
  m_components[m_object_to_component_index[game_object.index]].mesh;
}

Handle MeshSystem::material(GameObject game_object) {
  m_components[m_object_to_component_index[game_object.index]].material;
}

void MeshSystem::tell(MessageArgument& arg) {
  auto* data =
      arg.getDataPointer<StandardEventMessage::UPDATED_WORLD_TRANSFORM>();

  m_components[m_object_to_component_index[data->object.index]]
      .world_transform = data->world_transform;
}

void MeshSystem::renderAll() {
  for (auto& component : m_components) {
    MessageArgument arg;
    arg.init<StandardEventMessage::RENDER_MESH>();
    auto* data = arg.getDataPointer<StandardEventMessage::RENDER_MESH>();

    data->world_transform = component.world_transform;
    data->mesh = component.mesh;
    data->material = component.material;

    m_message_box.postMessage(arg);
  }
}
}
