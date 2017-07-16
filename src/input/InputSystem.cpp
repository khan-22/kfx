#include "kfx/input/InputSystem.h"

namespace kfx {
InputSystem::InputSystem(MessageBox &message_box) : Listener(message_box) {
  GLFWwindow *window = glfwGetCurrentContext();
  glfwSetWindowUserPointer(window, &message_box);
  glfwSetKeyCallback(window, InputSystem::key_callback);
  glfwSetCursorPosCallback(window, InputSystem::cursor_position_callback);
}

InputSystem::~InputSystem() {}

void InputSystem::tell(Message message) { return; }

void InputSystem::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  MessageBox *message_box = static_cast<MessageBox *>(
      glfwGetWindowUserPointer(glfwGetCurrentContext()));

  Message message = Message::makeKeyInputMessage(action, key, mods);
  message_box->postMessage(message);
}

void InputSystem::cursor_position_callback(GLFWwindow *window, double xpos,
                                           double ypos) {
  MessageBox *message_box = static_cast<MessageBox *>(
      glfwGetWindowUserPointer(glfwGetCurrentContext()));

  Message message = Message::makeMouseMoveMessage(xpos, ypos);
  message_box->postMessage(message);
}

void InputSystem::mouse_button_callback(int button, int action, int mods) {
  MessageBox *message_box = static_cast<MessageBox *>(
      glfwGetWindowUserPointer(glfwGetCurrentContext()));

  Message message = Message::makeMouseInputMessage(action, button, mods);
  message_box->postMessage(message);
}
}
