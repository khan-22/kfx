/***********************************/
/* Test: mesh-manager              */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/res/MeshManager.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// SCENARIO("Adding a mesh to the mesh manager", "[mesh]") {
//   REQUIRE(glfwInit() == GLFW_TRUE);

//   // Invisible window for the test...
//   glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
//   GLFWwindow* offscreen_context =
//       glfwCreateWindow(640, 480, "kfx_test", nullptr, nullptr);
//   REQUIRE(offscreen_context != NULL);
//   glfwMakeContextCurrent(offscreen_context);

//   REQUIRE(glewInit() == GLEW_OK);

//   kfx::MeshManager mesh_manager;

//   GIVEN("A list of vertices and indices") {
//     std::vector<kfx::Vertex3D> vertices = {
//         {{-1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//         {{0.f, 1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//         {{1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//     };
//     std::vector<GLuint> indices = {0, 1, 2};

//     WHEN("being loaded into the mesh manager") {
//       kfx::Handle mesh_handle =
//           mesh_manager.loadMeshFromMemory("test", vertices, indices);
//       THEN("a valid handle to the mesh object is returned") {
//         REQUIRE(mesh_handle.m_is_initialized == true);

//         kfx::Mesh* mesh =
//             mesh_manager.getMeshes().getResourceEntry(mesh_handle);

//         REQUIRE(glIsVertexArray(mesh->vertex_array_object) == GL_TRUE);
//         for (int i = 0; i < kfx::Mesh::NUM_BUFFERS; i++) {
//           REQUIRE(glIsBuffer(mesh->vertex_buffer_objects[i]) == GL_TRUE);
//         }
//         REQUIRE(mesh->draw_count > 0);

//         AND_THEN("the mesh is added to the array of meshes") {
//           auto& meshes = mesh_manager.getMeshes();

//           REQUIRE(meshes.resource.size() == 1);
//         }
//       }

//       AND_WHEN("more meshes are loaded into the mesh manager") {
//         kfx::Handle mesh_handle_2 =
//             mesh_manager.loadMeshFromMemory("test2", vertices, indices);
//         kfx::Handle mesh_handle_3 =
//             mesh_manager.loadMeshFromMemory("test3", vertices, indices);
//         kfx::Handle mesh_handle_4 =
//             mesh_manager.loadMeshFromMemory("test4", vertices, indices);

//         THEN("they all remain valid") {
//           REQUIRE(mesh_handle.m_is_initialized == true);
//           REQUIRE(mesh_handle_2.m_is_initialized == true);
//           REQUIRE(mesh_handle_3.m_is_initialized == true);
//           REQUIRE(mesh_handle_4.m_is_initialized == true);

//           kfx::Mesh* mesh =
//               mesh_manager.getMeshes().getResourceEntry(mesh_handle);
//           kfx::Mesh* mesh_2 =
//               mesh_manager.getMeshes().getResourceEntry(mesh_handle_2);
//           kfx::Mesh* mesh_3 =
//               mesh_manager.getMeshes().getResourceEntry(mesh_handle_3);
//           kfx::Mesh* mesh_4 =
//               mesh_manager.getMeshes().getResourceEntry(mesh_handle_4);

//           REQUIRE(glIsVertexArray(mesh->vertex_array_object) == GL_TRUE);
//           REQUIRE(glIsVertexArray(mesh_2->vertex_array_object) == GL_TRUE);
//           REQUIRE(glIsVertexArray(mesh_3->vertex_array_object) == GL_TRUE);
//           REQUIRE(glIsVertexArray(mesh_4->vertex_array_object) == GL_TRUE);
//           for (int i = 0; i < kfx::Mesh::NUM_BUFFERS; i++) {
//             REQUIRE(glIsBuffer(mesh->vertex_buffer_objects[i]) == GL_TRUE);
//             REQUIRE(glIsBuffer(mesh_2->vertex_buffer_objects[i]) == GL_TRUE);
//             REQUIRE(glIsBuffer(mesh_3->vertex_buffer_objects[i]) == GL_TRUE);
//             REQUIRE(glIsBuffer(mesh_4->vertex_buffer_objects[i]) == GL_TRUE);
//           }

//           REQUIRE(mesh->draw_count > 0);
//           REQUIRE(mesh_2->draw_count > 0);
//           REQUIRE(mesh_3->draw_count > 0);
//           REQUIRE(mesh_4->draw_count > 0);

//           AND_THEN("the meshes are added to the array of meshes") {
//             auto& meshes = mesh_manager.getMeshes();

//             REQUIRE(meshes.resource.size() == 4);
//           }
//         }
//       }
//     }
//   }

//   // GIVEN("A path to a valid mesh file") {
//   //   WHEN("passed into loadMeshFromFile(string)") {
//   //     THEN("a valid handle to the mesh object is returned") {
//   //       // ...
//   //       FAIL();
//   //     }
//   //   }
//   // }

//   GIVEN("A string with the name of an already loaded mesh") {
//     std::string mesh_name = "test";
//     std::vector<kfx::Vertex3D> vertices = {
//         {{-1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//         {{0.f, 1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//         {{1.f, -1.f, 0.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
//     };
//     std::vector<GLuint> indices = {0, 1, 2};
//     mesh_manager.loadMeshFromMemory(mesh_name, vertices, indices);

//     WHEN("being passed into getMeshByName(string)") {
//       THEN("a valid handle to the mesh object is returned") {
//         kfx::Handle mesh_handle = mesh_manager.getMeshByName(mesh_name);

//         REQUIRE(mesh_handle.m_is_initialized == true);

//         kfx::Mesh* mesh =
//             mesh_manager.getMeshes().getResourceEntry(mesh_handle);

//         REQUIRE(glIsVertexArray(mesh->vertex_array_object) == GL_TRUE);
//         for (int i = 0; i < kfx::Mesh::NUM_BUFFERS; i++) {
//           REQUIRE(glIsBuffer(mesh->vertex_buffer_objects[i]) == GL_TRUE);
//         }
//         REQUIRE(mesh->draw_count > 0);
//       }
//     }
//   }

//   glfwTerminate();
// }
