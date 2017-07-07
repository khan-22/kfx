#include <iostream>
#include <algorithm>
#include <string>
//#include <unistd.h>

#include <GL/glew.h>
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
	std::cout << "BAP " << num_msg() << std::endl;

	A test;
	test.a = 100;
	std::cout << test.a << std::endl;

	MyClass mc(5, 5);
	std::cout << mc.calcArea() << std::endl;

	int glfw_success = glfwInit();
	if (!glfw_success)
	{
		std::cerr << "Failed to init GLFW!" << std::endl;
		return -1;
	}
	std::cout << glfw_success << std::endl;


	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create a window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	unsigned int glew_success = glewInit();
	if (glew_success)
	{
		std::cerr << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		std::cin.ignore();
		std::cin.get();
		return -1;
	}



	glfwSetKeyCallback(window, key_callback);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);




	glClearColor(0.6f, 0.2f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		//glClearColor((rand() % 100) / 100.f, (rand() % 100) / 100.f, (rand() % 100) / 100.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
