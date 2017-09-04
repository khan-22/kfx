#include "kfx/MouseInputPeripheral.h"

#include "kfx/Engine.h"

#include "kfx/StandardEventMessage.h"

namespace kfx {
static struct PreviousEventData {
  float xpos;
  float ypos;
  float dx;
  float dy;
} previous_event_data;

MouseInputPeripheral::MouseInputPeripheral(MessageBox& message_box,
                                           Window& window)
    : InputPeripheral(message_box) {
  window.setMousePositionCallback(cursor_position_callback);
  window.setMouseButtonCallback(mouse_button_callback);
}

void MouseInputPeripheral::cursor_position_callback(GLFWwindow* window,
                                                    double xpos, double ypos) {
  Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

  Message msg = MouseMove{static_cast<float>(xpos) - previous_event_data.xpos,
                          static_cast<float>(ypos) - previous_event_data.ypos,
                          static_cast<float>(xpos), static_cast<float>(ypos)};

  previous_event_data.dx = static_cast<float>(xpos) - previous_event_data.xpos;
  previous_event_data.dy = static_cast<float>(ypos) - previous_event_data.ypos;
  previous_event_data.xpos = static_cast<float>(xpos);
  previous_event_data.ypos = static_cast<float>(ypos);

  engine->getMessageBox().postMessage(msg);
}

void MouseInputPeripheral::mouse_button_callback(GLFWwindow* window, int button,
                                                 int action, int mods) {
  Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

  Message msg = MouseAction{button, action, mods, previous_event_data.xpos,
                            previous_event_data.ypos};

  engine->getMessageBox().postMessage(msg);
}
}
