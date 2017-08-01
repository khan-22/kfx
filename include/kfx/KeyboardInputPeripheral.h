/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef KEYBOARD_INPUT_PERIPHERAL_H
#define KEYBOARD_INPUT_PERIPHERAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/ObservableSubject.h"
#include "kfx/ObserverInterface.h"
#include "kfx/Window.h"

namespace kfx {
class KeyboardInputPeripheral : public ObservableSubject {
 public:
  KeyboardInputPeripheral(Window &window);

 private:
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

  static void cursor_position_callback(GLFWwindow *window, double xpos,
                                       double ypos);

  static void mouse_button_callback(int button, int action, int mods);
};
}
#endif  // KEYBOARD_INPUT_PERIPHERAL_H
