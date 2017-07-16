#include "kfx/system/GraphicsSystem3D.h"

// TEMPORARY!!
#include <iostream>

namespace kfx {
GraphicsSystem3D::GraphicsSystem3D(GameObjectFactory* game_object_factory)
    : System(game_object_factory) {
  // ...
}

GraphicsSystem3D::~GraphicsSystem3D() {
  // ...
}

void GraphicsSystem3D::update(float dt) {
  // ...

  HandleManager& handle_manager = m_game_object_factory->getHandleManager();

  for (auto& object : m_game_object_factory->getGameObjects()) {
    std::cout << "Object has component? ["
              << (object.hasComponent(ComponentType::TRANSFORM) ? "YES]"
                                                                : "NO]")
              << std::endl;

    TransformComponent* transform_component = static_cast<TransformComponent*>(
        handle_manager.getEntry(object.getComponent(ComponentType::TRANSFORM)));

    transform_component->x += 0.01f;
    std::cout << "X: " << transform_component->x << std::endl;
  }
}
}
