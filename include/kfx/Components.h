/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "kfx/Handle.h"

namespace kfx {
enum ComponentType { TRANSFORM, MESH, NUM_TYPES };

class TransformComponent {
 public:
  TransformComponent();

  void lookAt(glm::vec3 target, glm::vec3 up);
  glm::mat4 getModel();

 private:
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;

  glm::mat4 m_model;
  bool m_should_update;
};

class MeshComponent {
 public:
  Handle mesh_handle;
  Handle shader_handle;

 private:
};

// class Component {
//  public:
//   virtual ~Component() {}

//  protected:
//   Component() {}

//  private:
// };
}

#endif  // COMPONENT_H
