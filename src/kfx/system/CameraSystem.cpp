#include "kfx/system/CameraSystem.h"

namespace kfx {

CameraSystem::CameraSystem(MessageBox& message_box,
                           TransformSystem& transform_system)
    : m_message_box(message_box), m_transform_system(transform_system) {
  //
}

CameraSystem::~CameraSystem() {
  //
}

void CameraSystem::addCamera(GameObject game_object) {
  m_single_component_system.addComponentToObject(game_object, glm::mat4(1.f));
}

void CameraSystem::removeCamera(GameObject game_object) {
  m_single_component_system.removeComponentFromObject(game_object);
}

void CameraSystem::submitCameras() {
  for (auto& dirty_object : m_transform_system.queryDirtyObjects()) {
    if (m_single_component_system.objectHasComponent(dirty_object)) {
      m_single_component_system.objectToComponent(dirty_object).view_transform =
          glm::inverse(m_transform_system.getWorldTransform(dirty_object));
    }
  }

  for (auto& component : m_single_component_system.getComponents()) {
    Message msg = SubmitViewport{component.view_transform};

    m_message_box.postMessage(msg);
  }
}
}
