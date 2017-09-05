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

  bool objectHasComponent(GameObject game_object);
  FpsInputComponent& objectToComponent(GameObject game_object);

  // std::vector<KeyAction> m_queued_keypresses;

  TransformSystem& m_transform_system;

  std::vector<uint32_t> m_object_to_component_index;
  std::vector<FpsInputComponent> m_components;

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
