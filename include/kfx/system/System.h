/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#include "kfx/GameObject.h"
#include "kfx/GameObjectFactory.h"

namespace kfx {
class System {
 public:
  virtual ~System();

  virtual void update(float dt) = 0;

 protected:
  System(GameObjectFactory& game_object_factory);
  GameObjectFactory& m_game_object_factory;
};
}
#endif  // SYSTEM_H
