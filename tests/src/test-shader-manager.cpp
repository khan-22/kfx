/***********************************/
/* Test: shader-manager         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <fstream>

#include <kfx/res/ShaderManager.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(_WIN32)
#include <direct.h>
#endif

#include <stdlib.h>
#include <sys/stat.h>   // no clue why required -- man pages say so
#include <sys/types.h>  // required for stat.h

SCENARIO("Adding a shader to the shader manager", "[shader]") {
  REQUIRE(glfwInit() == GLFW_TRUE);

  // Invisible window for the test...
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow* offscreen_context =
      glfwCreateWindow(640, 480, "kfx_test", nullptr, nullptr);
  REQUIRE(offscreen_context != NULL);
  glfwMakeContextCurrent(offscreen_context);

  REQUIRE(glewInit() == GLEW_OK);

  kfx::ShaderManager shader_manager;

  GIVEN("A valid shader source file") {
    std::string vertex_shader_source(R"(
      #version 420
      layout(location = 0) in vec3 position;
      uniform mat4 u_MVP;
      void main()
      {
        gl_Position = u_MVP * vec4(position, 1.0);  
      }
    )");

    int nError = 0;
#if defined(_WIN32)
    nError = _mkdir("test_shader");
#else
    mode_t nMode = 0733;
    nError = mkdir("test_shader", nMode);
#endif

    std::ofstream shader_file_output("./test_shader/test_shader.vs");
    REQUIRE(shader_file_output.is_open());
    shader_file_output << vertex_shader_source << std::endl;
    shader_file_output.close();

    WHEN("loading the file using the shader manager") {
      kfx::Handle handle = shader_manager.loadShaderFromFile("./test_shader");

      THEN("a valid handle to the shader is returned") {
        REQUIRE(handle != kfx::Handle::NULL_HANDLE);

        kfx::Shader* shader =
            shader_manager.getShaders().getResourceEntry(handle);

        REQUIRE(glIsProgram(shader->program) == GL_TRUE);
      }

      AND_WHEN("attempting to get/load the shader again") {
        kfx::Handle handle_b =
            shader_manager.loadShaderFromFile("./test_shader");
        kfx::Handle handle_c = shader_manager.getShaderByName("test_shader");

        THEN("the correct handle is returned") {
          REQUIRE(handle_b == handle);
          REQUIRE(handle_c == handle);
        }
      }
    }
  }

  GIVEN("An invalid shader source file") {
    std::string invalid_vertex_shader_source(R"(
      #version 420
      layout(location = 0) in vec3 position;
      uniform mat4 u_MVP;
      void main()
      {
        gl_Position = u_MVP * vec4ffj(position, 1.0);  
      }
    )");

    int nError = 0;
#if defined(_WIN32)
    nError = _mkdir("invalid_test_shader");
#else
    mode_t nMode = 0733;
    nError = mkdir("invalid_test_shader", nMode);
#endif

    std::ofstream shader_file_output(
        "./invalid_test_shader/invalid_test_shader.vs");
    REQUIRE(shader_file_output.is_open());
    shader_file_output << invalid_vertex_shader_source << std::endl;
    shader_file_output.close();

    WHEN("loading the file using the shader manager") {
      THEN("the function throws") {
        REQUIRE_THROWS(
            shader_manager.loadShaderFromFile("./invalid_test_shader"));
      }

      AND_WHEN("attempting to get the shader again") {
        kfx::Handle handle =
            shader_manager.getShaderByName("invalid_test_shader");
        THEN("a null handle is returned") {
          REQUIRE(handle == kfx::Handle::NULL_HANDLE);
        }
      }
    }
  }
}
