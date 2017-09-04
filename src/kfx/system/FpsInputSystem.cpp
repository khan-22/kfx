#include "kfx/system/FpsInputSystem.h"

#include "kfx/Log.h"

namespace kfx {
FpsInputSystem::FpsInputSystem(MessageBox& message_box,
                               TransformSystem& transform_system)
    : EventListener(message_box), m_transform_system(transform_system) {
  m_message_box.registerListener<KeyAction>(this);
  m_message_box.registerListener<MouseMove>(this);
  dx = dy = 0.f;
}

FpsInputSystem::~FpsInputSystem() { m_message_box.unregisterListener(this); }

void FpsInputSystem::addFpsControls(GameObject game_object) {
  FpsInputComponent new_component;
  new_component.object = game_object;
  new_component.local_position =
      m_transform_system.getLocalPosition(game_object);
  new_component.local_rotation =
      m_transform_system.getLocalRotation(game_object);

  m_components.push_back(new_component);

  if (m_object_to_component_index.size() < game_object.index + 1) {
    m_object_to_component_index.resize(game_object.index + 1);
  }

  m_object_to_component_index[game_object.index] = m_components.size() - 1;
}

void FpsInputSystem::removeFpsControls(GameObject game_object) {
  FpsInputComponent& this_component = objectToComponent(game_object);
  FpsInputComponent& last_component = m_components.back();

  this_component = last_component;
  m_components.pop_back();

  GameObject last_object = last_component.object;
  m_object_to_component_index[last_object.index] =
      m_object_to_component_index[game_object.index];

  m_object_to_component_index[game_object.index] = 0;
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
    dx += data->dx;
    dy += data->dy;
    LOG("Mouse message received: ", data->dx, "  ", data->dy);
  }
}

void FpsInputSystem::applyInput(float dt) {
  for (auto& dirty_object : m_transform_system.queryDirtyComponents()) {
    if (objectHasComponent(dirty_object)) {
      objectToComponent(dirty_object).local_position =
          m_transform_system.getLocalPosition(dirty_object);
      objectToComponent(dirty_object).local_rotation =
          m_transform_system.getLocalRotation(dirty_object);
    }
  }

  glm::vec3 delta_position(0.f);
  if (m_active_movement.test(FORWARD)) {
    delta_position.z += 1.f;
  }
  if (m_active_movement.test(BACKWARD)) {
    delta_position.z -= 1.f;
  }
  if (m_active_movement.test(LEFT)) {
    delta_position.x += 1.f;
  }
  if (m_active_movement.test(RIGHT)) {
    delta_position.x -= 1.f;
  }

  delta_position.y = -dy;
  delta_position *= dt;

  for (auto& component : m_components) {
    component.local_position += delta_position;
    m_transform_system.setLocalPosition(component.object,
                                        component.local_position);
  }

  dx = dy = 0.f;
}

bool FpsInputSystem::objectHasComponent(GameObject game_object) {
  for (auto& component : m_components) {
    if (component.object.id == game_object.id) {
      return true;
    }
  }
  return false;
}

FpsInputSystem::FpsInputComponent& FpsInputSystem::objectToComponent(
    GameObject game_object) {
  return m_components[m_object_to_component_index[game_object.index]];
}
}
