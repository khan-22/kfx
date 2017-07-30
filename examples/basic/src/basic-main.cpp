/***********************************/
/* Example: basic                  */
/* By: Karl Hansson 2017           */
/***********************************/

#include <iostream>

#include <kfx/Window.h>

int main() {
  std::cout << "Example: basic" << std::endl << std::endl;

#ifndef NDEBUG
  std::cout << "Debug" << std::endl;
#else
  std::cout << "Release" << std::endl;
#endif  // NDEBUG

  kfx::Window window(640, 480, "basic example");

  window.setClearColor(0.f, 0.f, 0.f);
  window.clear();
  window.swapBuffers();

  std::cin.ignore();
  std::cin.get();

  return 0;
}
