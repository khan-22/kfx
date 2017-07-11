/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <GLFW/glfw3.h>

#include "kfx/Listener.h"

namespace kfx
{
class InputSystem : public Listener
{
public:
  InputSystem(MessageBox &message_box);
  ~InputSystem() override;

  // Implementation simply returns since
  // InputSystem listens to no other subsystems
  void tell(Message message) final override;

private:
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);

  static void cursor_position_callback(GLFWwindow *window, double xpos,
                                       double ypos);

	static void mouse_button_callback(int button, int action, int mods);
};
}

#endif // INPUT_SYSTEM_H
