#include "kfx/system/TransformSystem.h"

namespace kfx {

TransformSystem::TransformSystem(MessageBox& message_box)
    : m_message_box(message_box) {  // EventListener(message_box) {
  // m_message_box.registerListener
}

TransformSystem::~TransformSystem() {
  //
}

void TransformSystem::addTransform(GameObject game_object, glm::vec3 position,
                                   glm::vec3 rotation) {
  TransformComponent new_component;
  new_component.object = game_object;
  new_component.local_position = position;
  new_component.local_rotation = rotation;
  new_component.updateWorldTransform();
  markComponentDirty(game_object);

  m_components.push_back(new_component);

  if (m_object_to_component_index.size() < game_object.index + 1) {
    m_object_to_component_index.resize(game_object.index + 1);
  }

  m_object_to_component_index[game_object.index] = m_components.size() - 1;
}

void TransformSystem::removeTransform(GameObject game_object) {
  TransformComponent& this_component =
      m_components[m_object_to_component_index[game_object.index]];
  TransformComponent& last_component = m_components.back();

  this_component = last_component;
  m_components.pop_back();

  GameObject last_object = last_component.object;
  m_object_to_component_index[last_object.index] =
      m_object_to_component_index[game_object.index];

  m_object_to_component_index[game_object.index] = 0;
}

glm::vec3 TransformSystem::getLocalPosition(GameObject game_object) const {
  return m_components[m_object_to_component_index[game_object.index]]
      .local_position;
}

glm::vec3 TransformSystem::getLocalRotation(GameObject game_object) const {
  return m_components[m_object_to_component_index[game_object.index]]
      .local_rotation;
}

void TransformSystem::setLocalPosition(GameObject game_object,
                                       glm::vec3 position) {
  TransformComponent& component = objectToComponent(game_object);

  component.local_position = position;
  component.updateWorldTransform();
  markComponentDirty(game_object);
}

void TransformSystem::setLocalRotation(GameObject game_object,
                                       glm::vec3 rotation) {
  TransformComponent& component = objectToComponent(game_object);

  component.local_rotation = rotation;
  component.updateWorldTransform();
  markComponentDirty(game_object);
}

glm::mat4 TransformSystem::getWorldTransform(GameObject game_object) {
  return objectToComponent(game_object).world_transform;
}

const std::vector<GameObject>& TransformSystem::queryDirtyComponents() {
  return m_dirty_components;
}

void TransformSystem::TransformComponent::updateWorldTransform() {
  glm::mat4 translation_matrix = glm::translate(local_position);

  glm::mat4 rot_x_matrix =
      glm::rotate(local_rotation.x, glm::vec3(1.f, 0.f, 0.f));
  glm::mat4 rot_y_matrix =
      glm::rotate(local_rotation.y, glm::vec3(0.f, 1.f, 0.f));
  glm::mat4 rot_z_matrix =
      glm::rotate(local_rotation.z, glm::vec3(0.f, 0.f, 1.f));

  glm::mat4 rotation_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;

  // glm::mat4 scale_matrix = glm::scale(m_scale);

  world_transform = translation_matrix * rotation_matrix;  //* scale_matrix;

  //   Message msg = UpdatedWorldTransform{object, world_transform};
  //   message_box.postMessage(msg);
}

TransformSystem::TransformComponent& TransformSystem::objectToComponent(
    GameObject game_object) {
  return m_components[m_object_to_component_index[game_object.index]];
}

void TransformSystem::markComponentDirty(GameObject object) {
  for (auto& dirty_object : m_dirty_components) {
    if (dirty_object.id == object.id) {
      return;
    }
  }

  m_dirty_components.push_back(object);
}
}
