#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
//#include <unistd.h>

#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "kfx/Listener.h"
#include "kfx/MessageBox.h"

#include "kfx/input/InputSystem.h"

#include "kfx/GameObjectFactory.h"
#include "kfx/resources/MeshManager.h"
#include "kfx/system/GraphicsSystem3D.h"

#include "kfx/Engine.h"

namespace kfx {
class DebugListener : public Listener {
 public:
  DebugListener(MessageBox &message_box) : Listener(message_box) {}
  ~DebugListener() override {}

  void tell(Message message) final override {
    std::cout << message.debug_msg << std::endl;
  }

 private:
};
class TestListener : public Listener {
 public:
  TestListener(MessageBox &message_box) : Listener(message_box) {}
  ~TestListener() override {}

  void tell(Message message) final override {
    std::cout << "(" << message.test_x << "," << message.test_y << ","
              << message.test_z << ")" << std::endl;
  }

 private:
};
class KeyInputListener : public Listener {
 public:
  KeyInputListener(MessageBox &message_box) : Listener(message_box) {}
  ~KeyInputListener() override {}

  void tell(Message message) final override {
    // std::cout << "(" << glfwGetKeyName(message.key_input_key, 0) << ")" <<
    // std::endl;
    printf("%s",
           message.key_input_action == GLFW_PRESS
               ? "PRESS: "
               : message.key_input_action == GLFW_RELEASE ? "RELEASE: "
                                                          : "REPEAT: ");

    if (message.key_input_mods & GLFW_MOD_ALT) {
      printf("%s", "<ALT>");
    }
    if (message.key_input_mods & GLFW_MOD_CONTROL) {
      printf("%s", "<CTRL>");
    }
    if (message.key_input_mods & GLFW_MOD_SHIFT) {
      printf("%s", "<SHIFT>");
    }
    if (message.key_input_mods & GLFW_MOD_SUPER) {
      printf("%s", "<SUPER>");
    }

    printf("(%s)\n", glfwGetKeyName(message.key_input_key, 0));

    if (message.key_input_action == GLFW_PRESS &&
        message.key_input_key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
  }

 private:
};
}

namespace kfx {
class MyTest : public kfx::Engine {
 public:
  MyTest() : Engine() {}
  ~MyTest() override {}

  void init() override {
    Engine::init();

    std::vector<kfx::Vertex3D> vertices = {
        {{-1.f, -1.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{-1.f, 1.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{1.f, 1.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{1.f, -1.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},

        {{-1.f, -1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{-1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{1.f, 1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{1.f, -1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
    };
    std::vector<GLuint> indices = {
        0, 1, 2, 0, 2, 3,  // Front
        4, 5, 6, 4, 6, 7,  // Back
        0, 4, 5, 0, 5, 1,  // Left
        3, 7, 6, 3, 6, 2,  // Right
        1, 5, 6, 1, 6, 2,  // Top
        0, 4, 7, 0, 7, 3,  // Bottom
    };

    m_mesh_manager.loadMeshFromMemory("test", vertices, indices);

    m_shader_manager.loadShaderFromFile("./res/shaders/basic");

    m_game_object_factory.createTestObject();
  }

 private:
};
}

GLFWwindow *initialize();
GLFWwindow *initialize() {
  int glfw_success = glfwInit();
  if (!glfw_success) {
    std::cerr << "Failed to init GLFW!" << std::endl;
    return nullptr;
  }
  std::cout << glfw_success << std::endl;

  GLFWwindow *window = glfwCreateWindow(640, 640, "kfx", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create a window!" << std::endl;
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);

  unsigned int glew_success = glewInit();
  if (glew_success) {
    std::cerr << "Failed to initialize glew!" << std::endl;
    glfwTerminate();
    return nullptr;
  }

  return window;
}

int main() {
  std::cout << "Initializing..." << std::endl;

  GLFWwindow *window = initialize();
  if (window == nullptr) {
    std::cin.ignore();
    std::cin.get();
    return -1;
  }

  using namespace kfx;
  MessageBox message_box;
  DebugListener debug_listener(message_box);
  TestListener test_listener(message_box);

  // Only posts messages, so is never registered...
  InputSystem input_system(message_box);
  KeyInputListener input_listener(message_box);
  message_box.registerListener(&input_listener, Message::KEY_INPUT);

  message_box.registerListener(&debug_listener, Message::DEBUG);

  Message debug_message = Message::makeDebugMessage(
      "Hello Message Box! "
      "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"
      "dddddd");
  Message test_message = Message::makeTestMessage(1, 2, 3);
  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  message_box.registerListener(&test_listener, Message::TEST);

  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  message_box.unregisterListener(&debug_listener);

  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  kfx::MyTest my_test;
  my_test.init();

  // glUseProgram(program);
  glClearColor(0.6f, 0.2f, 0.3f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    message_box.distributeMessages();

    my_test.update(0.1f);

    my_test.render();

    // glBindVertexArray(vao);
    // glUseProgram(program);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
