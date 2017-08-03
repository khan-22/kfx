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

  MessageArgument message(StandardEventMessage::KEY_ACTION);
  auto* data =
      reinterpret_cast<EventArgumentData<StandardEventMessage::KEY_ACTION>*>(
          message.data.get());
  data->action = action;
  data->key = key;
  data->scancode = scancode;
  data->mods = mods;

  engine->getMessageBox().postMessage(message);
}
}
