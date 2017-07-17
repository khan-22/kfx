/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "kfx/Handle.h"

namespace kfx {
enum ComponentType { TRANSFORM, MESH, NUM_TYPES };

class TransformComponent {
 public:
  float x, y, z;

 private:
};

class MeshComponent {
 public:
  Handle mesh_handle;

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
