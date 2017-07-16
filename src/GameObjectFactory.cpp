#include "kfx/GameObjectFactory.h"

namespace kfx {
Handle GameObjectFactory::createTestObject() {
  m_game_objects.emplace_back();
  GameObject &object = m_game_objects.back();

  m_transform_components.emplace_back();
  TransformComponent &transform_component = m_transform_components.back();

  Handle transform_component_handle =
      m_handle_manager.addEntry(&transform_component);

  object.addComponent(ComponentType::TRANSFORM, transform_component_handle);

  Handle object_handle = m_handle_manager.addEntry(&object);

  return object_handle;
}

HandleManager &GameObjectFactory::getHandleManager() {
  return m_handle_manager;
}

std::vector<GameObject> &GameObjectFactory::getGameObjects() {
  return m_game_objects;
}
}
