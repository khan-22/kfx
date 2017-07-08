#include <iostream>
#include <algorithm>
#include <string>
//#include <unistd.h>

#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "keyboard.h"


static void key_callback(
	GLFWwindow* window, int key, int scancode, 
	int action, int mods);

static void key_callback(
	GLFWwindow* window, int key, int scancode, 
	int action, int mods)
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

GLFWwindow* initialize();
GLFWwindow* initialize()
{
	int glfw_success = glfwInit();
	if (!glfw_success)
	{
		std::cerr << "Failed to init GLFW!" << std::endl;
		return nullptr;
	}
	std::cout << glfw_success << std::endl;

	GLFWwindow* window = glfwCreateWindow(640, 480, "kfx", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create a window!" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	unsigned int glew_success = glewInit();
	if (glew_success)
	{
		std::cerr << "Failed to initialize glew!" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwSetKeyCallback(window, key_callback);

	return window;
}

GLuint create_shader();
GLuint create_shader()
{
	GLuint program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);

	{	
		std::ifstream shaderFile(std::string("./res/shaders/basic.vs"));
		std::string shaderText((std::istreambuf_iterator<char>(shaderFile)),
				std::istreambuf_iterator<char>());
		shaderFile.close();
		const char* shaderTextPtr = shaderText.c_str();
		std::cout << shaderText << std::endl;
		glShaderSource(vs, 1, &shaderTextPtr, nullptr);
		glCompileShader(vs);

		GLint	success = 0;
		GLchar	vsError[1024] = { 0 };
		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
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
		const char* shaderTextPtr = shaderText.c_str();
		std::cout << shaderText << std::endl;
		glShaderSource(fs, 1, &shaderTextPtr, nullptr);
		glCompileShader(fs);

		GLint success = 0;
		GLchar fsError[1024] = { 0 };
		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
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
	if (success == GL_FALSE)
	{
		GLchar error[1024] = { 0 };

		glGetProgramInfoLog(program, sizeof(error), nullptr, error);
		
		std::cout << ">> LINKING ERRORS -------------------------" 
				<< std::endl;
		std::cout << error << std::endl;
		// std::cout << std::endl;
		// std::cout << shaderTextPtr;
	}

	return program;
}

int main()
{
	std::cout << "BAP " << num_msg() << std::endl;

	A test;
	test.a = 100;
	std::cout << test.a << std::endl;

	MyClass mc(5, 5);
	std::cout << mc.calcArea() << std::endl;

	GLFWwindow* window = initialize();
	if (window == nullptr)
	{
		std::cin.ignore();
		std::cin.get();
		return -1;
	}

	struct Vertex
	{
		float x,y,z;
	};

	Vertex vertices[] = {
		Vertex{-1.f, -1.f, 0.f},
		Vertex{ 1.f, -1.f, 0.f},
		Vertex{ 0.f,  1.f, 0.f},
	};

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 3,
			vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glBindVertexArray(0);

	GLuint program = create_shader();

	glClearColor(0.6f, 0.2f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
