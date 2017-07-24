#include "kfx/GameObject.h"

#include "kfx/Assert.h"

namespace kfx {
// void GameObject::addComponent(ComponentType type, Handle handle) {
//   kfx_assert(type >= 0);
//   kfx_assert(type < ComponentType::NUM_TYPES);
//   kfx_assert(handle.m_is_initialized == true);

//   m_components[type] = handle;
// }

Handle GameObject::getComponent(ComponentType type) {
  kfx_assert(type >= 0);
  kfx_assert(type < ComponentType::NUM_TYPES);

  return m_components[type];
}

bool GameObject::hasComponent(ComponentType type) {
  kfx_assert(type >= 0);
  kfx_assert(type < ComponentType::NUM_TYPES);

  return m_components[type].m_is_initialized;
}
}
