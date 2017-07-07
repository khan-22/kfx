#include <iostream>
#include <algorithm>
#include <string>
#include <unistd.h>

#include <fstream>

#include <GLFW/glfw3.h>

#include "keyboard.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

struct A
{
  int a;
  int b;
};

int main()
{
  std::cout << "JENNIFER DUMPED ME BAP " << num_msg() << std::endl;

  A test;
  test.a = 100;
  std::cout << test.a << std::endl;
  
  MyClass mc(5,5);
  std::cout << mc.calcArea() << std::endl;

  auto success = glfwInit();
  if (!success)
  {
    std::cerr << "Failed to init GLFW!" << std::endl;
    return -1;
  }
  std::cout << success << std::endl;


  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Failed to create a window!" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
