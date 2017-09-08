/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef FPS_INPUT_SYSTEM_H
#define FPS_INPUT_SYSTEM_H

#include <bitset>
#include <glm/glm.hpp>
#include <vector>

#include "kfx/EventListener.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/MessageBox.h"

#include "kfx/system/TransformSystem.h"

#include "kfx/system/SingleComponentSystem.h"

namespace kfx {
class FpsInputSystem : public EventListener {
 public:
  FpsInputSystem(MessageBox& message_box, TransformSystem& transform_system);
  ~FpsInputSystem() final override;

  void addFpsControls(GameObject game_object);
  void removeFpsControls(GameObject game_object);

  void tell(Message& msg) final override;

  void applyInput(float dt);

 private:
  struct FpsInputComponent {
    GameObject object;
    glm::vec3 local_position;
    glm::vec3 local_rotation;
  };

  SingleComponentSystem<FpsInputComponent, false> m_single_component_system;

  TransformSystem& m_transform_system;

  float mouse_dx, mouse_dy;
  enum MOVEMENT_FLAGS {
    FORWARD,
    LEFT,
    RIGHT,
    BACKWARD,

    NUM_FLAGS
  };
  std::bitset<MOVEMENT_FLAGS::NUM_FLAGS> m_active_movement;
};
}
#endif  // FPS_INPUT_SYSTEM_H
