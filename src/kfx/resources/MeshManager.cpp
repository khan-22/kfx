#include "kfx/resources/MeshManager.h"

#include "kfx/resources/MeshUtil.h"

#include "kfx/Assert.h"

namespace kfx {
Handle loadMeshFromFile(const fs::path path) {
  // Not implemented yet
  kfx_contract(false);

  return Handle::NULL_HANDLE;
}

Handle MeshManager::loadMeshFromMemory(const std::string name,
                                       const std::vector<Vertex3D>& vertices,
                                       const std::vector<GLuint>& indices) {
  // If the mesh has already been loaded, return the handle
  Handle found_handle = getMeshByName(name);
  if (found_handle != Handle::NULL_HANDLE) {
    return found_handle;
  }

  // Place the new mesh into the array of meshes
  // m_meshes.emplace_back();
  // Mesh& mesh = m_meshes.back();
  Handle mesh_handle = m_meshes.addResourceEntry(vertices, indices);
  if (mesh_handle == Handle::NULL_HANDLE) {
    return Handle::NULL_HANDLE;
  }

  // Mesh* mesh = m_meshes.getResourceEntry(mesh_handle);
  // *mesh = util::meshFromData(vertices, indices);

  // Create a new handle to the resources
  // Handle mesh_handle = m_mesh_handle_manager.addEntry(&mesh);

  // Pair the name and the handle for future look-ups
  m_name_to_handle_map[name] = mesh_handle;

  return mesh_handle;
}

// HandleManager& MeshManager::getHandleManager() { return
// m_mesh_handle_manager; }

Handle MeshManager::getMeshByName(const std::string name) {
  auto it = m_name_to_handle_map.find(name);
  if (it != m_name_to_handle_map.end()) {
    return it->second;
  } else {
    return Handle::NULL_HANDLE;
  }
}

HandledResource<Mesh>& MeshManager::getMeshes() { return m_meshes; }
}
