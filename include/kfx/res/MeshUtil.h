/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESH_UTIL_H
#define MESH_UTIL_H

#include <vector>

#include "kfx/res/Mesh.h"
#include "kfx/res/Vertex3D.h"

namespace kfx {
namespace util {
Mesh meshFromData(const std::vector<Vertex3D>& vertices,
                  const std::vector<GLuint>& indices);
}
}

#endif  // MESH_UTIL_H
