#include "kfx/KeyboardInputPeripheral.h"

#include "kfx/Engine.h"
#include "kfx/StandardObserverMessage.h"

namespace kfx {
KeyboardInputPeripheral::KeyboardInputPeripheral(Window& window) {
  window.setKeyCallback(key_callback);
}

void KeyboardInputPeripheral::key_callback(GLFWwindow* window, int key,
                                           int scancode, int action, int mods) {
  Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

  ObserverArgument arg;
  arg.type = StandardObserverMessage::KEY_PRESSED;

  ObserverArgumentData<KEY_PRESSED> data;
  data.key = key;
  data.scancode = scancode;
  data.mods = mods;

  arg.data = &data;

  engine->getKeyboardInputPeripheral().notify(arg);
}
}
