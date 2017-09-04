/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "kfx/Handle.h"
#include "kfx/HandleManager.h"
#include "kfx/graphics/Mesh.h"
#include "kfx/graphics/Vertex3D.h"

#include "kfx/resources/FileUtil.h"
#include "kfx/resources/HandledResource.h"

namespace kfx {
class MeshManager final {
 public:
  Handle loadMeshFromFile(const fs::path path);
  Handle loadMeshFromMemory(const std::string name,
                            const std::vector<Vertex3D>& vertices,
                            const std::vector<GLuint>& indices);

  Handle getMeshByName(const std::string name);

  HandledResource<Mesh>& getMeshes();

 private:
  std::unordered_map<std::string, Handle> m_name_to_handle_map;

  HandledResource<Mesh> m_meshes;
};
}
#endif  // MESH_MANAGER_H
