/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GRAPHICS_SYSTEM_3D_H
#define GRAPHICS_SYSTEM_3D_H

#include "kfx/system/System.h"

namespace kfx {
class GraphicsSystem3D : public System {
 public:
  GraphicsSystem3D(GameObjectFactory* game_object_factory);
  virtual ~GraphicsSystem3D();

  void update(float dt) final override;

 private:
};
}
#endif  // 3D_GRAPHICS_SYSTEM_H
