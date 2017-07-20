/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <GL/glew.h>
#include <string>

#include "kfx/graphics/Shader.h"

namespace kfx {
namespace util {
GLuint shaderStageFromData(std::string source, GLenum stage);

Shader shaderProgramFromStages(GLuint vertex_shader, GLuint geometry_shader,
                               GLuint fragment_shader);
}
}
#endif  // SHADER_UTIL_H
