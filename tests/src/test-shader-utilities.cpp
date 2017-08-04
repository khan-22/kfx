/***********************************/
/* Test: shader-utilities          */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Assert.h>
#include <kfx/resources/ShaderUtil.h>

#include <GLFW/glfw3.h>

SCENARIO("Creating a shader stage", "[util]") {
  REQUIRE(glfwInit() == GLFW_TRUE);

  // Invisible window for the test...
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow* offscreen_context =
      glfwCreateWindow(640, 480, "kfx_test", nullptr, nullptr);
  REQUIRE(offscreen_context != NULL);
  glfwMakeContextCurrent(offscreen_context);

  REQUIRE(glewInit() == GLEW_OK);

  GIVEN("A source string for a vertex shader") {
    std::string vertex_shader_src(R"(
      #version 420
      layout(location = 0) in vec3 position;
      uniform mat4 u_MVP;
      void main()
      {
        gl_Position = u_MVP * vec4(position, 1.0);  
      }
    )");

    WHEN("passed to the shaderStageFromData(string, type) function") {
      GLuint shader_handle =
          kfx::util::shaderStageFromData(vertex_shader_src, GL_VERTEX_SHADER);
      THEN("function returns a valid handle to a vertex shader") {
        REQUIRE(glIsShader(shader_handle) == GL_TRUE);
      }
    }

    WHEN(
        "passing an invalid type to the shaderStageFromData(string, type) "
        "function") {
      THEN("the function throws") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(vertex_shader_src, GL_FLOAT),
            kfx::KfxContractFailure);
      }
    }
  }

  GIVEN("A source string for a geometry shader") {
    std::string geometry_shader_src(R"(
      #version 420
      layout(triangles) in;
      layout(triangle_strip, max_vertices=3) out;
      void main()
      {
        for(int i = 0; i < gl_in.length(); i++) {
          gl_Position = gl_in[i].gl_Position;
          EmitVertex();
        }
      }
    )");

    WHEN("passed to the shaderStageFromData(string, type) function") {
      GLuint shader_handle = kfx::util::shaderStageFromData(geometry_shader_src,
                                                            GL_GEOMETRY_SHADER);
      THEN("the function returns a valid handle to a geometry shader") {
        REQUIRE(glIsShader(shader_handle) == GL_TRUE);
      }
    }

    WHEN(
        "passing an invalid type to the shaderStageFromData(string, type) "
        "function") {
      THEN("the function throws") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(geometry_shader_src, GL_FLOAT),
            kfx::KfxContractFailure);
      }
    }
  }

  GIVEN("A source string for a fragment shader") {
    std::string fragment_shader_src(R"(
      #version 420
      out vec4 frag_color;
      void main()
      {
        frag_color = vec4(1.0, 0.0, 1.0, 1.0);
      }
    )");

    WHEN("passed to the shaderStageFromData(string, type) function") {
      GLuint shader_handle = kfx::util::shaderStageFromData(fragment_shader_src,
                                                            GL_FRAGMENT_SHADER);
      THEN("the function returns a valid handle to a fragment shader") {
        REQUIRE(glIsShader(shader_handle) == GL_TRUE);
      }
    }

    WHEN(
        "passing an invalid type to the shaderStageFromData(string, type) "
        "function") {
      THEN("the function throws") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(fragment_shader_src, GL_FLOAT),
            kfx::KfxContractFailure);
      }
    }
  }

  GIVEN("An empty string") {
    std::string not_src("");

    WHEN(
        "passed to the shaderStageFromData(string, type) function as a vertex "
        "shader") {
      GLuint shader_handle =
          kfx::util::shaderStageFromData(not_src, GL_VERTEX_SHADER);
      THEN("the function returns an invalid shader handle") {
        REQUIRE(glIsShader(shader_handle) == GL_FALSE);
      }
    }
    WHEN(
        "passed to the shaderStageFromData(string, type) function as a "
        "geometry "
        "shader") {
      GLuint shader_handle =
          kfx::util::shaderStageFromData(not_src, GL_GEOMETRY_SHADER);
      THEN("the function returns an invalid shader handle") {
        REQUIRE(glIsShader(shader_handle) == GL_FALSE);
      }
    }
    WHEN(
        "passed to the shaderStageFromData(string, type) function as a "
        "fragment "
        "shader") {
      GLuint shader_handle =
          kfx::util::shaderStageFromData(not_src, GL_FRAGMENT_SHADER);
      THEN("the function returns an invalid shader handle") {
        REQUIRE(glIsShader(shader_handle) == GL_FALSE);
      }
    }
  }

  GIVEN("A string that is not valid source code (non-empty)") {
    std::string not_src(R"(
      #Garbo Garbo 
      void main() { return garbo }
    )");

    WHEN(
        "passed to the shaderStageFromData(string, type) function as a vertex "
        "shader") {
      THEN("the function aborts") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(not_src, GL_VERTEX_SHADER),
            kfx::KfxAbortFailure);
      }
    }
    WHEN(
        "passed to the shaderStageFromData(string, type) function as a "
        "geometry "
        "shader") {
      THEN("the function aborts") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(not_src, GL_GEOMETRY_SHADER),
            kfx::KfxAbortFailure);
      }
    }
    WHEN(
        "passed to the shaderStageFromData(string, type) function as a "
        "fragment "
        "shader") {
      THEN("the function aborts") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderStageFromData(not_src, GL_FRAGMENT_SHADER),
            kfx::KfxAbortFailure);
      }
    }
  }

  glfwTerminate();
}

SCENARIO("Creating a shader program", "util") {
  REQUIRE(glfwInit() == GLFW_TRUE);

  // Invisible window for the test...
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow* offscreen_context =
      glfwCreateWindow(640, 480, "kfx_test", nullptr, nullptr);
  REQUIRE(offscreen_context != NULL);
  glfwMakeContextCurrent(offscreen_context);

  REQUIRE(glewInit() == GLEW_OK);

  GIVEN("Three valid shader stages (vertex, geometry, fragment)") {
    std::string vertex_shader_src(R"(
      #version 420
      layout(location = 0) in vec3 position;
      uniform mat4 u_MVP;
      void main()
      {
        gl_Position = u_MVP * vec4(position, 1.0);  
      }
    )");
    std::string geometry_shader_src(R"(
      #version 420
      layout(triangles) in;
      layout(triangle_strip, max_vertices=3) out;
      void main()
      {
        for(int i = 0; i < gl_in.length(); i++) {
          gl_Position = gl_in[i].gl_Position;
          EmitVertex();
        }
      }
    )");
    std::string fragment_shader_src(R"(
      #version 420
      out vec4 frag_color;
      void main()
      {
        frag_color = vec4(1.0, 0.0, 1.0, 1.0);
      }
    )");
    GLuint vertex_shader_handle =
        kfx::util::shaderStageFromData(vertex_shader_src, GL_VERTEX_SHADER);
    GLuint geometry_shader_handle =
        kfx::util::shaderStageFromData(geometry_shader_src, GL_GEOMETRY_SHADER);
    GLuint fragment_shader_handle =
        kfx::util::shaderStageFromData(fragment_shader_src, GL_FRAGMENT_SHADER);

    REQUIRE(glIsShader(vertex_shader_handle) == GL_TRUE);
    REQUIRE(glIsShader(geometry_shader_handle) == GL_TRUE);
    REQUIRE(glIsShader(fragment_shader_handle) == GL_TRUE);

    WHEN(
        "Vertex, Geometry and Fragment shaders are passed to "
        "shaderProgramFromStages(vert, geom, frag)") {
      THEN("the function returns a valid shader object") {
        REQUIRE(glIsProgram(kfx::util::shaderProgramFromStages(
                                vertex_shader_handle, geometry_shader_handle,
                                fragment_shader_handle)
                                .program) == GL_TRUE);
      }
    }

    WHEN(
        "Only vertex and fragment shaders are passed to "
        "shaderProgramFromStages(vert, geom, frag)") {
      THEN("the function returns a valid shader object") {
        REQUIRE(glIsProgram(kfx::util::shaderProgramFromStages(
                                vertex_shader_handle, 0, fragment_shader_handle)
                                .program) == GL_TRUE);
      }
    }

    WHEN(
        "Only the vertex shader is passed to "
        "shaderProgramFromStages(vert, geom, frag)") {
      THEN("the function returns a valid shader object") {
        REQUIRE(glIsProgram(kfx::util::shaderProgramFromStages(
                                vertex_shader_handle, 0, 0)
                                .program) == GL_TRUE);
      }
    }

    WHEN(
        "Only the geometry shader is passed to "
        "shaderProgramFromStages(vert, geom, frag)") {
      THEN("the function aborts") {
        REQUIRE_THROWS_AS(
            kfx::util::shaderProgramFromStages(geometry_shader_handle, 0, 0),
            kfx::KfxAbortFailure);
      }
    }

    WHEN(
        "Only the fragment shader is passed to "
        "shaderProgramFromStages(vert, geom, frag)") {
      THEN("the function returns a valid shader object") {
        REQUIRE(glIsProgram(kfx::util::shaderProgramFromStages(
                                0, 0, fragment_shader_handle)
                                .program) == GL_TRUE);
      }
    }
  }

  glfwTerminate();
}