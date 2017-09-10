/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "kfx/MessageBox.h"

#include "kfx/system/TransformSystem.h"

#include "kfx/system/SingleComponentSystem.h"

namespace kfx {
class CameraSystem {
 public:
  CameraSystem(MessageBox& message_box, TransformSystem& transform_system);
  ~CameraSystem();

  void addCamera(GameObject game_object);
  void removeCamera(GameObject game_object);

  void submitCameras();

 private:
  struct CameraComponent {
    GameObject object;
    glm::mat4 view_transform;
  };

  SingleComponentSystem<CameraComponent, false> m_single_component_system;

  MessageBox& m_message_box;

  TransformSystem& m_transform_system;
};
}
#endif  // CAMERA_SYSTEM_H
