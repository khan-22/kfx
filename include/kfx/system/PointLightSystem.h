/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef POINT_LIGHT_SYSTEM_H
#define POINT_LIGHT_SYSTEM_H

#include "kfx/MessageBox.h"

#include "kfx/system/TransformSystem.h"

#include "kfx/system/SingleComponentSystem.h"

namespace kfx {
class PointLightSystem {
 public:
  PointLightSystem(MessageBox& message_box, TransformSystem& transform_system);
  ~PointLightSystem();

  void addPointLight(GameObject game_object, glm::vec3 position,
                     glm::vec3 color, float radius);
  void removePointLight(GameObject game_object);

  void submitLights();

 private:
  struct PointLightComponent {
    GameObject object;
    glm::vec3 position;
    glm::vec3 color;
    float radius;
  };

  SingleComponentSystem<PointLightComponent, false> m_single_component_system;

  MessageBox& m_message_box;

  TransformSystem& m_transform_system;
};
}
#endif  // POINT_LIGHT_SYSTEM_H
