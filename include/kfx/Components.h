/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

namespace kfx {
enum ComponentType { TRANSFORM, NUM_TYPES };

class TransformComponent {
 public:
  float x, y, z;

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
