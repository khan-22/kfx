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

  double previous_time = glfwGetTime();
  while (window.isOpen()) {
    double current_time = glfwGetTime();
    double dt = current_time - previous_time;

    my_test.update(static_cast<float>(dt));
    my_test.render();

    static int counter = 0;
    if (counter++ == 60) {
      std::cout << 1.0 / dt << std::endl;
      counter = 0;
    }

    previous_time = current_time;
  }

  std::cin.ignore();
  std::cin.get();

  return 0;
}
