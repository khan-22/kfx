#include "kfx/Clock.h"

#include <GLFW/glfw3.h>

namespace kfx {
Clock::Clock() : m_previous_time(glfwGetTime()) {
  // ...
}

double Clock::reset() {
  double current_time = glfwGetTime();
  double difference = current_time - m_previous_time;
  m_previous_time = current_time;
  return difference;
}

double Clock::look() { return glfwGetTime() - m_previous_time; }
}
