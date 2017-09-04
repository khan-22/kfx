/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef KEYBOARD_INPUT_PERIPHERAL_H
#define KEYBOARD_INPUT_PERIPHERAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/InputPeripheral.h"
#include "kfx/Window.h"

namespace kfx {
class KeyboardInputPeripheral : public InputPeripheral {
 public:
  KeyboardInputPeripheral(MessageBox &message_box, Window &window);
  ~KeyboardInputPeripheral() final override = default;

 private:
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
};
}
#endif  // KEYBOARD_INPUT_PERIPHERAL_H
