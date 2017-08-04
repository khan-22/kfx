/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace kfx {
class Window final {
 public:
  Window(int width, int height, std::string title);
  Window(int width, int height, std::string title, int hint, int value);
  ~Window();

  // Window should not be copyable or moveable
  Window(const Window&) = delete;
  Window(const Window&&) = delete;
  Window& operator=(const Window&) = delete;
  Window& operator=(const Window&&) = delete;

  bool isOpen();
  void close();

  void setClearColor(const float r, const float g, const float b,
                     const float a = 1.f);
  void clear();
  void swapBuffers();

  void setGLFWUserData(void* data);

  int getWidth() const;
  int getHeight() const;
  std::string getTitle() const;

  void setKeyCallback(GLFWkeyfun func);

 private:
  int m_width;
  int m_height;
  std::string m_title;

  GLFWwindow* m_window;

  static int window_counter;
};
}
#endif  // WINDOW_H
