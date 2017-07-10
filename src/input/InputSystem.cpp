#include "kfx/input/InputSystem.h"

namespace kfx
{
InputSystem::InputSystem(MessageBox &message_box) : Listener(message_box)
{
  glfwSetWindowUserPointer(glfwGetCurrentContext(), &message_box);
}

InputSystem::~InputSystem() {}

void InputSystem::tell(Message message) { return; }

void InputSystem::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods)
{
  MessageBox *message_box = static_cast<MessageBox *>(
      glfwGetWindowUserPointer(glfwGetCurrentContext()));

  Message message = Message::makeKeyInputMessage(action, key, scancode);
  message_box->postMessage(message);
}
}

void InputSystem::cursor_position_callback(GLFWwindow *window, double xpos,
                                           double ypos)
{
  MessageBox *message_box = static_cast<MessageBox *>(
      glfwGetWindowUserPointer(glfwGetCurrentContext()));

  Message message = Message::makeMouseMoveMessage(xpos, ypos);
  message_box->postMessage(message);
}