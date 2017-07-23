/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#include "kfx/GameObject.h"
#include "kfx/GameObjectFactory.h"

// #include "kfx/Engine.h"

namespace kfx {
// Forward-declaration
class Engine;

class System {
 public:
  virtual ~System();

  virtual void update(float dt) = 0;

 protected:
  System(Engine *engine);
  Engine *m_engine;
};
}
#endif  // SYSTEM_H
