#include "kfx/KeyboardInputPeripheral.h"

#include "kfx/Engine.h"
#include "kfx/StandardObserverMessage.h"

#include "kfx/Assert.h"

namespace kfx {
KeyboardInputPeripheral::KeyboardInputPeripheral(Window& window) {
  window.setKeyCallback(key_callback);
}

void KeyboardInputPeripheral::key_callback(GLFWwindow* window, int key,
                                           int scancode, int action, int mods) {
  Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

  ObserverArgument arg;
  switch (action) {
    case GLFW_PRESS: {
      arg.type = StandardObserverMessage::KEY_PRESSED;
      ObserverArgumentData<StandardObserverMessage::KEY_PRESSED> data;
      data.key = key;
      data.scancode = scancode;
      data.mods = mods;

      arg.data = &data;
      engine->getKeyboardInputPeripheral().notify(arg);
      break;
    }
    case GLFW_REPEAT: {
      arg.type = StandardObserverMessage::KEY_REPEAT;
      ObserverArgumentData<StandardObserverMessage::KEY_REPEAT> data;
      data.key = key;
      data.scancode = scancode;
      data.mods = mods;

      arg.data = &data;
      engine->getKeyboardInputPeripheral().notify(arg);
      break;
    }
    case GLFW_RELEASE: {
      arg.type = StandardObserverMessage::KEY_RELEASED;
      ObserverArgumentData<StandardObserverMessage::KEY_RELEASED> data;
      data.key = key;
      data.scancode = scancode;
      data.mods = mods;

      arg.data = &data;
      engine->getKeyboardInputPeripheral().notify(arg);
      break;
    }
    default:
      // This code should never run
      kfx_abort();
  }
}
}
