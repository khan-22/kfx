/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESH_SYSTEM_H
#define MESH_SYSTEM_H

#include <glm/glm.hpp>
#include <vector>

#include "kfx/EventListener.h"
#include "kfx/GameObject.h"
#include "kfx/Handle.h"
#include "kfx/MessageBox.h"

#include "kfx/system/TransformSystem.h"

namespace kfx {
class MeshSystem /* : public EventListener*/ {
 public:
  MeshSystem(MessageBox& message_box, TransformSystem& transform_system);
  ~MeshSystem();  // final override;

  void addMesh(GameObject game_object, Handle mesh, Handle material);
  void removeMesh(GameObject game_object);
  Handle mesh(GameObject game_object);
  Handle material(GameObject game_object);

  // void tell(Message& msg) final override;

  // Temporary until a better solution is found...
  void renderAll();

 private:
  struct MeshComponent {
    GameObject object;
    glm::mat4 world_transform;
    Handle mesh;
    Handle material;
  };

  MeshComponent& objectToComponent(GameObject game_object);

  MessageBox& m_message_box;

  TransformSystem& m_transform_system;

  std::vector<uint32_t> m_object_to_component_index;
  std::vector<MeshComponent> m_components;
};
}
#endif  // MESH_SYSTEM_H
