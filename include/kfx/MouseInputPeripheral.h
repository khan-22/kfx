/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MOUSE_INPUT_PERIPHERAL_H
#define MOUSE_INPUT_PERIPHERAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/InputPeripheral.h"
#include "kfx/Window.h"

namespace kfx {
class MouseInputPeripheral : public InputPeripheral {
 public:
  MouseInputPeripheral(MessageBox& message_box, Window& window);
  ~MouseInputPeripheral() final override = default;

 private:
  static void cursor_position_callback(GLFWwindow* window, double xpos,
                                       double ypos);

  static void mouse_button_callback(GLFWwindow* window, int button, int action,
                                    int mods);
};
}
#endif  // MOUSE_INPUT_PERIPHERAL_H
