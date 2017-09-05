#include "kfx/res/ShaderUtil.h"

#include <iostream>
#include "kfx/Assert.h"

namespace kfx {
namespace util {
GLuint shaderStageFromData(std::string source, GLenum stage) {
  kfx_contract(stage == GL_VERTEX_SHADER || stage == GL_GEOMETRY_SHADER ||
               stage == GL_FRAGMENT_SHADER);

  if (source.length() == 0) {
    return 0;
  }

  GLuint shader = glCreateShader(stage);
  kfx_contract(shader != 0);

  const GLchar* c_source = source.c_str();

  glShaderSource(shader, 1, &c_source, nullptr);
  glCompileShader(shader);

  // If something goes wrong, print the error and simply abort the process...
  // I currently don't want the process to continue should there be anything
  // wrong with the shaders.

  GLint compile_status = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_FALSE) {
    GLint log_length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* compile_log = new GLchar[static_cast<size_t>(log_length)];

    glGetShaderInfoLog(shader, log_length, nullptr, compile_log);

    std::cerr << "^=========================^" << std::endl;
    switch (stage) {
      case GL_VERTEX_SHADER:
        std::cerr << "Vertex";
        break;
      case GL_GEOMETRY_SHADER:
        std::cerr << "Geometry";
        break;
      case GL_FRAGMENT_SHADER:
        std::cerr << "Fragment";
        break;
    }
    std::cerr << " shader compilation error!\n" << compile_log << std::endl;
    std::cerr << "v=========================v" << std::endl;

    delete[] compile_log;

    kfx_abort();
  }

  return shader;
}

Shader shaderProgramFromStages(GLuint vertex_shader, GLuint geometry_shader,
                               GLuint fragment_shader) {
  // Shader shader;
  // shader.program = glCreateProgram();

  // glAttachShader(shader.program, vertex_shader);
  // if (geometry_shader > 0) {
  //   glAttachShader(shader.program, geometry_shader);
  // }
  // glAttachShader(shader.program, fragment_shader);

  // glLinkProgram(shader.program);

  // // If something goes wrong, print the error and simply kfx_ the process...
  // // I currently don't want the process to continue should there be anything
  // // wrong with the shaders.
  // GLint link_status = GL_FALSE;
  // glGetProgramiv(shader.program, GL_LINK_STATUS, &link_status);
  // if (link_status == GL_FALSE) {
  //   GLint log_length = 0;
  //   glGetProgramiv(shader.program, GL_INFO_LOG_LENGTH, &log_length);

  //   GLchar* link_log = new GLchar[static_cast<size_t>(log_length)];

  //   glGetProgramInfoLog(shader.program, log_length, nullptr, link_log);

  //   std::cerr << "^=========================^" << std::endl;
  //   std::cerr << "shader linking error!\n" << link_log << std::endl;
  //   std::cerr << "v=========================v" << std::endl;

  //   delete[] link_log;

  //   kfx_abort();
  // }

  // return shader;
}
}
}
