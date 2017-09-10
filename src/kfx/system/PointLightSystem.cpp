#include "kfx/system/PointLightSystem.h"

namespace kfx {
PointLightSystem::PointLightSystem(MessageBox& message_box,
                                   TransformSystem& transform_system)
    : m_message_box(message_box), m_transform_system(transform_system) {
  //
}

PointLightSystem::~PointLightSystem() {
  //
}

void PointLightSystem::addPointLight(GameObject game_object, glm::vec3 position,
                                     glm::vec3 color, float radius) {
  m_single_component_system.addComponentToObject(game_object, position, color,
                                                 radius);
}

void PointLightSystem::removePointLight(GameObject game_object) {
  m_single_component_system.removeComponentFromObject(game_object);
}

void PointLightSystem::submitLights() {
  for (auto& dirty_object : m_transform_system.queryDirtyObjects()) {
    if (m_single_component_system.objectHasComponent(dirty_object)) {
      m_single_component_system.objectToComponent(dirty_object).position =
          m_transform_system.getWorldTransform(dirty_object)[3];
    }
  }

  for (auto& component : m_single_component_system.getComponents()) {
    Message msg =
        SubmitPointLight{component.position, component.color, component.radius};

    m_message_box.postMessage(msg);
  }
}
}
