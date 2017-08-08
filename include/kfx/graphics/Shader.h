/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

namespace kfx {
class Shader {
 public:
  Shader(GLuint vertex_shader, GLuint geometry_shader, GLuint fragment_shader);
  Shader(Shader&& other);
  ~Shader();

  void operator=(Shader&& other);

  GLuint program;

 private:
  // No copying allowed
  Shader(const Shader& other) = delete;
  void operator=(const Shader& other) = delete;
};
}
#endif  // SHADER_H
