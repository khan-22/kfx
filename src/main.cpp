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
    printf("%s", message.key_input_action == GLFW_PRESS
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

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

GLFWwindow *initialize();
GLFWwindow *initialize() {
  int glfw_success = glfwInit();
  if (!glfw_success) {
    std::cerr << "Failed to init GLFW!" << std::endl;
    return nullptr;
  }
  std::cout << glfw_success << std::endl;

  GLFWwindow *window = glfwCreateWindow(640, 480, "kfx", nullptr, nullptr);
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

  glfwSetKeyCallback(window, key_callback);

  return window;
}

GLuint create_shader();
GLuint create_shader() {
  GLuint program = glCreateProgram();

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);

  {
    std::ifstream shaderFile(std::string("./res/shaders/basic.vs"));
    std::string shaderText((std::istreambuf_iterator<char>(shaderFile)),
                           std::istreambuf_iterator<char>());
    shaderFile.close();
    const char *shaderTextPtr = shaderText.c_str();
    std::cout << shaderText << std::endl;
    glShaderSource(vs, 1, &shaderTextPtr, nullptr);
    glCompileShader(vs);

    GLint success = 0;
    GLchar vsError[1024] = {0};
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      glGetShaderInfoLog(vs, sizeof(vsError), nullptr, vsError);

      std::cout << ">> VERTEX SHADER ERRORS -------------------------"
                << std::endl;
      std::cout << std::endl << vsError << std::endl;
    }

    glAttachShader(program, vs);
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

  {
    std::ifstream shaderFile(std::string("./res/shaders/basic.fs"));
    std::string shaderText((std::istreambuf_iterator<char>(shaderFile)),
                           std::istreambuf_iterator<char>());
    shaderFile.close();
    const char *shaderTextPtr = shaderText.c_str();
    std::cout << shaderText << std::endl;
    glShaderSource(fs, 1, &shaderTextPtr, nullptr);
    glCompileShader(fs);

    GLint success = 0;
    GLchar fsError[1024] = {0};
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      glGetShaderInfoLog(fs, sizeof(fsError), nullptr, fsError);

      std::cout << ">> FRAGMENT SHADER ERRORS -------------------------"
                << std::endl;
      std::cout << std::endl << fsError << std::endl;
    }
    glAttachShader(program, fs);
  }
  glLinkProgram(program);

  GLint success = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLchar error[1024] = {0};

    glGetProgramInfoLog(program, sizeof(error), nullptr, error);

    std::cout << ">> LINKING ERRORS -------------------------" << std::endl;
    std::cout << error << std::endl;
    // std::cout << std::endl;
    // std::cout << shaderTextPtr;
  }

  return program;
}

int main() {
	std::cout << "Initializing..." << std::endl;

  GLFWwindow *window = initialize();
  if (window == nullptr) {
    std::cin.ignore();
    std::cin.get();
    return -1;
  }

  // struct Vertex {
  //   float x, y, z;
  // };

  // Vertex vertices[] = {
  //     Vertex{-1.f, -1.f, 0.f}, Vertex{1.f, -1.f, 0.f}, Vertex{0.f, 1.f, 0.f},
  // };

  // GLuint vao = 0;
  // glGenVertexArrays(1, &vao);
  // glBindVertexArray(vao);

  // glEnableVertexAttribArray(0);

  // GLuint vbo = 0;
  // glGenBuffers(1, &vbo);
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 3, vertices,
  //              GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

  // glBindVertexArray(0);

  GLuint program = create_shader();

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
  message_box.postMessage(debug_message);
  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  message_box.registerListener(&test_listener, Message::TEST);

  message_box.postMessage(debug_message);
  message_box.postMessage(debug_message);
  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  message_box.unregisterListener(&debug_listener);

  message_box.postMessage(debug_message);
  message_box.postMessage(debug_message);
  message_box.postMessage(debug_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.postMessage(test_message);
  message_box.distributeMessages();

  MeshManager mesh_manager;
  std::vector<Vertex3D> vertices = {
      {{-1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
      {{0.f, 1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
      {{1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
  };
  mesh_manager.loadMeshFromMemory("test", vertices);

  GameObjectFactory factory(mesh_manager);
  GraphicsSystem3D graphics_system(factory, mesh_manager);
  factory.createTestObject();

  glUseProgram(program);
  glClearColor(0.6f, 0.2f, 0.3f, 1.0f);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    message_box.distributeMessages();

    graphics_system.update(0.1f);

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
