#include "kfx/KeyboardInputPeripheral.h"

#include "kfx/Engine.h"

#include "kfx/Assert.h"

#include "kfx/StandardEventMessage.h"

namespace kfx {
KeyboardInputPeripheral::KeyboardInputPeripheral(MessageBox& message_box,
                                                 Window& window)
    : InputPeripheral(message_box) {
  window.setKeyCallback(key_callback);
}

void KeyboardInputPeripheral::key_callback(GLFWwindow* window, int key,
                                           int scancode, int action, int mods) {
  Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

  Message msg = KeyAction{action, key, scancode, mods};
  engine->getMessageBox().postMessage(msg);
}
}
