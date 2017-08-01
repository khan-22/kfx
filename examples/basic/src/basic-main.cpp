/***********************************/
/* Example: basic                  */
/* By: Karl Hansson 2017           */
/***********************************/

#include <iostream>

#include <kfx/Engine.h>
#include <kfx/Window.h>

class MyTest : public kfx::Engine {
 public:
  MyTest(kfx::Window& window) : Engine(window) {}
  ~MyTest() override {}

  void init() override {
    Engine::init();

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

    m_mesh_manager.loadMeshFromMemory("test", vertices, indices);

    m_shader_manager.loadShaderFromFile("./res/shaders/basic");

    m_game_object_factory.createTestObject();
  }

 private:
};

int main() {
  std::cout << "Example: basic" << std::endl << std::endl;

#ifndef NDEBUG
  std::cout << "Debug" << std::endl;
#else
  std::cout << "Release" << std::endl;
#endif  // NDEBUG

  kfx::Window window(640, 480, "basic example");

  MyTest my_test(window);
  my_test.init();

  window.setClearColor(0.f, 0.f, 0.f);

  while (window.isOpen()) {
    window.clear();
    my_test.update(0.1f);
    my_test.render();
    window.swapBuffers();

    glfwPollEvents();
  }

  std::cin.ignore();
  std::cin.get();

  return 0;
}
