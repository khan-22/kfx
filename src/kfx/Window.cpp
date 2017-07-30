#include "kfx/Window.h"

#include "kfx/Assert.h"

namespace kfx {

int Window::window_counter = 0;

Window::Window(int width, int height, std::string title)
    : m_width(width), m_height(height), m_title(title) {
  // There should be only one window per program
  kfx_contract(window_counter == 0);
  ++window_counter;

  auto glfw_success = glfwInit();
  kfx_contract(glfw_success);

  m_window =
      glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
  kfx_contract(m_window != nullptr);

  glfwMakeContextCurrent(m_window);

  auto glew_failure = glewInit();
  kfx_contract(!glew_failure);
}

Window::Window(int width, int height, std::string title, int hint, int value) {
  glfwWindowHint(hint, value);
  Window(width, height, title);
}

Window::~Window() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
  --window_counter;
}

bool Window::isOpen() { return glfwWindowShouldClose(m_window) == GLFW_FALSE; }

void Window::close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); }

void Window::setClearColor(const float r, const float g, const float b,
                           const float a) {
  glClearColor(r, g, b, a);
}

void Window::clear() {
  //...
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers() {
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

int Window::getWidth() const { return m_width; }
int Window::getHeight() const { return m_height; }
std::string Window::getTitle() const { return m_title; }
}
