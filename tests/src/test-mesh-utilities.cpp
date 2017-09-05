/***********************************/
/* Test: mesh-utilities            */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <kfx/Assert.h>
#include <kfx/res/MeshUtil.h>

SCENARIO("Creating a mesh", "[util]") {
  REQUIRE(glfwInit() == GLFW_TRUE);

  // Invisible window for the test...
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow* offscreen_context =
      glfwCreateWindow(640, 480, "kfx_test", nullptr, nullptr);
  REQUIRE(offscreen_context != NULL);
  glfwMakeContextCurrent(offscreen_context);

  REQUIRE(glewInit() == GLEW_OK);

  GIVEN("A list of vertices and a list of indices") {
    // A cube
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
    WHEN("passed to the meshFromData(vertices, indices) function") {
      THEN("the function returns a valid Mesh object") {
        kfx::Mesh mesh = kfx::util::meshFromData(vertices, indices);

        REQUIRE(glIsVertexArray(mesh.vertex_array_object) == GL_TRUE);

        for (int i = 0; i < kfx::Mesh::NUM_BUFFERS; i++) {
          REQUIRE(glIsBuffer(mesh.vertex_buffer_objects[i]) == GL_TRUE);
        }

        REQUIRE(mesh.draw_count > 0);
      }
    }
    //
  }

  GIVEN("An empty list of vertices and indices") {
    std::vector<kfx::Vertex3D> vertices = {};
    std::vector<GLuint> indices = {};
    WHEN("passed to the meshFromData(vertices, indices) function") {
      THEN("the function throws") {
        REQUIRE_THROWS_AS(kfx::util::meshFromData(vertices, indices),
                          kfx::KfxContractFailure);
      }
    }
  }
}
