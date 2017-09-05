/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef GRAPHICS_SYSTEM_3D_H
#define GRAPHICS_SYSTEM_3D_H

#include "kfx/res/MeshManager.h"
#include "kfx/res/ShaderManager.h"
#include "kfx/system/System.h"

#include "kfx/EventListener.h"
#include "kfx/MessageBox.h"

namespace kfx {
class GraphicsSystem3D final : public System, public EventListener {
 public:
  GraphicsSystem3D(MessageBox& message_box, Engine* engine);
  ~GraphicsSystem3D() final override;

  void update(float dt) final override;

  void tell(Message& msg) final override;

 private:
  float m_total_time;
};
}
#endif  // 3D_GRAPHICS_SYSTEM_H
