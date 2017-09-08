#include "kfx/system/FpsInputSystem.h"

#include "kfx/Log.h"

namespace kfx {
FpsInputSystem::FpsInputSystem(MessageBox& message_box,
                               TransformSystem& transform_system)
    : EventListener(message_box), m_transform_system(transform_system) {
  m_message_box.registerListener<KeyAction>(this);
  m_message_box.registerListener<MouseMove>(this);
  mouse_dx = mouse_dy = 0.f;
}

FpsInputSystem::~FpsInputSystem() {
  m_message_box.unregisterListener(this);  //
}

void FpsInputSystem::addFpsControls(GameObject game_object) {
  m_single_component_system.addComponentToObject(
      game_object,  //
      m_transform_system.getLocalPosition(game_object),
      m_transform_system.getLocalRotation(game_object));
}

void FpsInputSystem::removeFpsControls(GameObject game_object) {
  m_single_component_system.removeComponentFromObject(game_object);
}

void FpsInputSystem::tell(Message& msg) {
  if (auto data = std::get_if<KeyAction>(&msg)) {
    bool is_pressed = data->action != GLFW_RELEASE;
    switch (data->key) {
      case GLFW_KEY_W:
        m_active_movement.set(FORWARD, is_pressed);
        break;
      case GLFW_KEY_S:
        m_active_movement.set(BACKWARD, is_pressed);
        break;
      case GLFW_KEY_A:
        m_active_movement.set(LEFT, is_pressed);
        break;
      case GLFW_KEY_D:
        m_active_movement.set(RIGHT, is_pressed);
        break;
    }
  } else if (auto data = std::get_if<MouseMove>(&msg)) {
    mouse_dx += data->dx;
    mouse_dy += data->dy;
    // LOG("Mouse message received: ", data->dx, "  ", data->dy);
  }
}

void FpsInputSystem::applyInput(float dt) {
  for (auto& dirty_object : m_transform_system.queryDirtyObjects()) {
    if (m_single_component_system.objectHasComponent(dirty_object)) {
      m_single_component_system.objectToComponent(dirty_object).local_position =
          m_transform_system.getLocalPosition(dirty_object);
      m_single_component_system.objectToComponent(dirty_object).local_rotation =
          m_transform_system.getLocalRotation(dirty_object);
    }
  }

  float forward_factor = 0.f;
  float left_factor = 0.f;
  if (m_active_movement.test(FORWARD)) {
    forward_factor += 1.f;
  }
  if (m_active_movement.test(BACKWARD)) {
    forward_factor -= 1.f;
  }
  if (m_active_movement.test(LEFT)) {
    left_factor += 1.f;
  }
  if (m_active_movement.test(RIGHT)) {
    left_factor -= 1.f;
  }

  for (auto& component : m_single_component_system.getComponents()) {
    /*
      [ cy    sy*sp     -sy*cp ]
      [ 0     cp        sp     ]
      [ sy    -sp*cy    cy*cp  ]
    */
    component.local_rotation.x += -mouse_dy * dt;  // Pitch
    component.local_rotation.y += -mouse_dx * dt;  // Yaw

    const float PI = glm::pi<float>();
    const float HALF_PI = PI / 2.f;
    if (component.local_rotation.x >= HALF_PI) {
      component.local_rotation.x = HALF_PI - 0.01f;
    } else if (component.local_rotation.x < -HALF_PI) {
      component.local_rotation.x = -HALF_PI + 0.01f;
    }

    const float TWO_PI = 2.f * PI;
    if (component.local_rotation.y >= TWO_PI) {
      component.local_rotation.y -= TWO_PI;
    } else if (component.local_rotation.y < 0.f) {
      component.local_rotation.y += TWO_PI;
    }

    m_transform_system.setLocalRotation(component.object,
                                        component.local_rotation);

    const float CY = cosf(component.local_rotation.y);
    const float SY = sinf(component.local_rotation.y);
    const float CP = cosf(component.local_rotation.x);
    const float SP = sinf(component.local_rotation.x);

    const glm::vec3 forward_vector{-SY * CP, SP, -CY * CP};
    const glm::vec3 left_vector{-CY, 0.f, SY};

    const float SPEED = 4.f;

    glm::vec3 delta_position = SPEED * dt * (forward_vector * forward_factor +
                                             left_vector * left_factor);

    component.local_position += delta_position;
    m_transform_system.setLocalPosition(component.object,
                                        component.local_position);
  }

  mouse_dx = mouse_dy = 0.f;
}
}
