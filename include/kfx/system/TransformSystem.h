/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include <glm/glm.hpp>
#include <vector>

#include "kfx/EventListener.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/MessageBox.h"

#include "kfx/system/SingleComponentSystem.h"

namespace kfx {
class TransformSystem {
 public:
  TransformSystem(MessageBox& message_box);
  ~TransformSystem();

  void addTransform(GameObject game_object, glm::vec3 position,
                    glm::vec3 rotation);
  void removeTransform(GameObject game_object);

  glm::vec3 getLocalPosition(GameObject game_object);
  glm::vec3 getLocalRotation(GameObject game_object);
  void setLocalPosition(GameObject game_object, glm::vec3 position);
  void setLocalRotation(GameObject game_object, glm::vec3 rotation);

  glm::mat4 getWorldTransform(GameObject game_object);

  void clearDirtyObjects();
  const std::vector<GameObject>& queryDirtyObjects();

 private:
  struct TransformComponent {
    GameObject object;
    glm::mat4 world_transform;
    glm::vec3 local_position;
    glm::vec3 local_rotation;
  };

  void updateWorldTransform(GameObject game_object);

  SingleComponentSystem<TransformComponent, true> m_single_component_system;

  MessageBox& m_message_box;
};
}
#endif  // TRANSFORM_SYSTEM_H
