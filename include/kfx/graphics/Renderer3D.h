/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef RENDERER_3D_H
#define RENDERER_3D_H

#include <vector>

#include <glm/glm.hpp>

// #include "kfx/Engine.h"
#include "kfx/EventListener.h"
#include "kfx/Handle.h"

namespace kfx {
// Forward declaration
class Engine;

class Renderer3D : public EventListener {
 public:
  Renderer3D(MessageBox& message_box, Engine& engine);
  ~Renderer3D() final override;

  void tell(MessageArgument& arg) final override;

  void render();

 private:
  struct DrawCall {
    glm::mat4 model_transform;
    Handle mesh;
    Handle shader;
  };
  std::vector<DrawCall> m_draw_calls;

  Engine& m_engine;
};
}
#endif  // RENDERER_3D_H
