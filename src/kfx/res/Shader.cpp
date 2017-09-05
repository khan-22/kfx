#include "kfx/res/Shader.h"

#include <iostream>

#include "kfx/Assert.h"

namespace kfx {

Shader::Shader(GLuint vertex_shader, GLuint geometry_shader,
               GLuint fragment_shader) {
  this->program = glCreateProgram();

  glAttachShader(this->program, vertex_shader);
  if (geometry_shader > 0) {
    glAttachShader(this->program, geometry_shader);
  }
  glAttachShader(this->program, fragment_shader);

  glLinkProgram(this->program);

  // If something goes wrong, print the error and simply kfx_ the process...
  // I currently don't want the process to continue should there be anything
  // wrong with the shaders.
  GLint link_status = GL_FALSE;
  glGetProgramiv(this->program, GL_LINK_STATUS, &link_status);
  if (link_status == GL_FALSE) {
    GLint log_length = 0;
    glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* link_log = new GLchar[static_cast<size_t>(log_length)];

    glGetProgramInfoLog(this->program, log_length, nullptr, link_log);

    std::cerr << "^=========================^" << std::endl;
    std::cerr << "shader linking error!\n" << link_log << std::endl;
    std::cerr << "v=========================v" << std::endl;

    delete[] link_log;

    kfx_abort();
  }
}

Shader::Shader(Shader&& other) {
  this->program = std::move(other.program);  // <-

  other.program = 0;
}

Shader::~Shader() {
  glDeleteProgram(this->program);
  this->program = 0;
}

void Shader::operator=(Shader&& other) {
  if (this != &other) {
    this->program = std::move(other.program);

    other.program = 0;
  }
}
}
