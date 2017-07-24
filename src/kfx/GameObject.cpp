#include "kfx/GameObject.h"

#include <cassert>

namespace kfx {
// void GameObject::addComponent(ComponentType type, Handle handle) {
//   assert(type >= 0);
//   assert(type < ComponentType::NUM_TYPES);
//   assert(handle.m_is_initialized == true);

//   m_components[type] = handle;
// }

Handle GameObject::getComponent(ComponentType type) {
  assert(type >= 0);
  assert(type < ComponentType::NUM_TYPES);

  return m_components[type];
}

bool GameObject::hasComponent(ComponentType type) {
  assert(type >= 0);
  assert(type < ComponentType::NUM_TYPES);

  return m_components[type].m_is_initialized;
}
}
