#include "kfx/GameObject.h"

#include "kfx/Assert.h"

namespace kfx {
// void GameObject::addComponent(ComponentType type, Handle handle) {
//   kfx_contract(type >= 0);
//   kfx_contract(type < ComponentType::NUM_TYPES);
//   kfx_contract(handle.m_is_initialized == true);

//   m_components[type] = handle;
// }

Handle GameObject::getComponent(ComponentType type) {
  kfx_contract(type >= 0);
  kfx_contract(type < ComponentType::NUM_TYPES);

  return m_components[type];
}

bool GameObject::hasComponent(ComponentType type) {
  kfx_contract(type >= 0);
  kfx_contract(type < ComponentType::NUM_TYPES);

  return m_components[type].m_is_initialized;
}
}
