/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SINGLE_COMPONENT_SYSTEM_H
#define SINGLE_COMPONENT_SYSTEM_H

#include <vector>

#include "kfx/GameObject.h"

namespace kfx {

template <typename T, bool SHOULD_DIRTY>
class SingleComponentSystem {
 public:
  template <typename... MArgs>
  void addComponentToObject(GameObject game_object, MArgs... mArgs);
  void removeComponentFromObject(GameObject game_object);

  bool objectHasComponent(GameObject game_object);
  T& objectToComponent(GameObject game_object);

  void markDirty(GameObject game_object);
  std::vector<GameObject>& queryDirtyObjects();
  void clearDirtyObjects();

  std::vector<T>& getComponents();

 private:
  std::vector<uint32_t> m_object_to_component_index;
  std::vector<T> m_components;

  std::vector<GameObject> m_dirty_objects;
};

// ------------------------------------------
//
// ------------------------------------------

template <typename T, bool SHOULD_DIRTY>
template <typename... MArgs>
void SingleComponentSystem<T, SHOULD_DIRTY>::addComponentToObject(
    GameObject game_object, MArgs... mArgs) {
  T new_component{game_object, std::forward<MArgs>(mArgs)...};
  m_components.push_back(new_component);

  if (m_object_to_component_index.size() < game_object.index + 1) {
    m_object_to_component_index.resize(game_object.index + 1);
  }

  m_object_to_component_index[game_object.index] = m_components.size() - 1;
}

template <typename T, bool SHOULD_DIRTY>
void SingleComponentSystem<T, SHOULD_DIRTY>::removeComponentFromObject(
    GameObject game_object) {
  T& this_component = objectToComponent(game_object);
  T& last_component = m_components.back();

  this_component = last_component;
  m_components.pop_back();

  GameObject last_object = last_component.object;
  m_object_to_component_index[last_object.index] =
      m_object_to_component_index[game_object.index];

  m_object_to_component_index[game_object.index] = 0;
}

template <typename T, bool SHOULD_DIRTY>
bool SingleComponentSystem<T, SHOULD_DIRTY>::objectHasComponent(
    GameObject game_object) {
  for (auto& component : m_components) {
    if (component.object.id == game_object.id) {
      return true;
    }
  }
  return false;
}

template <typename T, bool SHOULD_DIRTY>
T& SingleComponentSystem<T, SHOULD_DIRTY>::objectToComponent(
    GameObject game_object) {
  return m_components[m_object_to_component_index[game_object.index]];
}

template <typename T, bool SHOULD_DIRTY>
void SingleComponentSystem<T, SHOULD_DIRTY>::markDirty(GameObject game_object) {
  if
    constexpr(SHOULD_DIRTY == false) { abort(); }

  for (auto& dirty_object : m_dirty_objects) {
    if (dirty_object.id == game_object.id) {
      return;
    }
  }

  m_dirty_objects.push_back(game_object);
}

template <typename T, bool SHOULD_DIRTY>
std::vector<GameObject>&
SingleComponentSystem<T, SHOULD_DIRTY>::queryDirtyObjects() {
  if
    constexpr(SHOULD_DIRTY == false) { abort(); }
  return m_dirty_objects;
}

template <typename T, bool SHOULD_DIRTY>
void SingleComponentSystem<T, SHOULD_DIRTY>::clearDirtyObjects() {
  if
    constexpr(SHOULD_DIRTY == false) { abort(); }

  m_dirty_objects.clear();
}

template <typename T, bool SHOULD_DIRTY>
std::vector<T>& SingleComponentSystem<T, SHOULD_DIRTY>::getComponents() {
  return m_components;
}
}
#endif  // SINGLE_COMPONENT_SYSTEM_H
