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
  m_single_component_system.addComponentToObject(game_object, glm::mat4(1.f),
                                                 position, rotation);
  updateWorldTransform(game_object);
  m_single_component_system.markDirty(game_object);
}

void TransformSystem::removeTransform(GameObject game_object) {
  m_single_component_system.removeComponentFromObject(game_object);
}

glm::vec3 TransformSystem::getLocalPosition(GameObject game_object) {
  return m_single_component_system.objectToComponent(game_object)
      .local_position;
}

glm::vec3 TransformSystem::getLocalRotation(GameObject game_object) {
  return m_single_component_system.objectToComponent(game_object)
      .local_rotation;
}

void TransformSystem::setLocalPosition(GameObject game_object,
                                       glm::vec3 position) {
  TransformComponent& component =
      m_single_component_system.objectToComponent(game_object);

  component.local_position = position;
  updateWorldTransform(game_object);
  m_single_component_system.markDirty(game_object);
}

void TransformSystem::setLocalRotation(GameObject game_object,
                                       glm::vec3 rotation) {
  TransformComponent& component =
      m_single_component_system.objectToComponent(game_object);

  component.local_rotation = rotation;
  updateWorldTransform(game_object);
  m_single_component_system.markDirty(game_object);
}

glm::mat4 TransformSystem::getWorldTransform(GameObject game_object) {
  return m_single_component_system.objectToComponent(game_object)
      .world_transform;
}

void TransformSystem::clearDirtyObjects() {
  m_single_component_system.clearDirtyObjects();
}

const std::vector<GameObject>& TransformSystem::queryDirtyObjects() {
  return m_single_component_system.queryDirtyObjects();
}

void TransformSystem::updateWorldTransform(GameObject game_object) {
  TransformComponent& component =
      m_single_component_system.objectToComponent(game_object);
  glm::mat4 translation_matrix = glm::translate(component.local_position);

  glm::mat4 rot_x_matrix =
      glm::rotate(component.local_rotation.x, glm::vec3(1.f, 0.f, 0.f));
  glm::mat4 rot_y_matrix =
      glm::rotate(component.local_rotation.y, glm::vec3(0.f, 1.f, 0.f));
  glm::mat4 rot_z_matrix =
      glm::rotate(component.local_rotation.z, glm::vec3(0.f, 0.f, 1.f));

  glm::mat4 rotation_matrix = rot_z_matrix * rot_y_matrix * rot_x_matrix;

  // glm::mat4 scale_matrix = glm::scale(m_scale);

  component.world_transform =
      translation_matrix * rotation_matrix;  //* scale_matrix;

  //   Message msg = UpdatedWorldTransform{object, world_transform};
  //   message_box.postMessage(msg);
}
}
