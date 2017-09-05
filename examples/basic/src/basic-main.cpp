/***********************************/
/* Example: basic                  */
/* By: Karl Hansson 2017           */
/***********************************/

#include <iostream>
#include <sstream>
#include <string>

#include <kfx/Clock.h>
#include <kfx/Engine.h>
#include <kfx/Window.h>

#include <kfx/resources/MaterialParser.h>

class MyTest : public kfx::Engine {
 public:
  MyTest(kfx::Window& window) : Engine(window) {}
  ~MyTest() override {}

  void init() override {
    Engine::init();

    std::vector<kfx::Vertex3D> vertices = {
        {{-1.f, -1.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{-1.f, 1.f, -1.f}, {0.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, 1.f, -1.f}, {1.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, -1.f, -1.f}, {1.f, 0.f}, {0.f, 0.f, 0.f}},

        {{-1.f, -1.f, 1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{-1.f, 1.f, 1.f}, {0.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, 1.f, 1.f}, {1.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, -1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f, 0.f}},
    };
    std::vector<GLuint> indices = {
        0, 1, 2, 0, 2, 3,  // Front
        4, 5, 6, 4, 6, 7,  // Back
        0, 4, 5, 0, 5, 1,  // Left
        3, 7, 6, 3, 6, 2,  // Right
        1, 5, 6, 1, 6, 2,  // Top
        0, 4, 7, 0, 7, 3,  // Bottom
    };

    std::vector<kfx::Vertex3D> vertices2 = {
        {{-1.f, 0.f, -1.f}, {0.f, 0.f}, {0.f, 0.f, 0.f}},
        {{-1.f, 0.f, 1.f}, {0.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, 0.f, 1.f}, {1.f, 1.f}, {0.f, 0.f, 0.f}},
        {{1.f, 0.f, -1.f}, {1.f, 0.f}, {0.f, 0.f, 0.f}},
    };
    std::vector<GLuint> indices2 = {
        0, 1, 2, 0, 2, 3,
    };

    const float SIZE = 32.f;
    for (auto& vertex : vertices2) {
      vertex.pos *= SIZE;
      vertex.uv *= SIZE;
    }

    m_mesh_manager.loadMeshFromMemory("test", vertices, indices);
    m_mesh_manager.loadMeshFromMemory("floor", vertices2, indices2);

    m_shader_manager.loadShaderFromFile("basic");
    m_texture_manager.loadTextureFromFile("test");

    m_material_manager.loadMaterialFromFile("test-material");
    m_material_manager.loadMaterialFromFile("missing");

    m_game_object_factory.createTestObject();
    m_game_object_factory.createStaticObject("floor", "missing",
                                             glm::vec3(0.f, -1.f, 0.f));
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

  //   std::string test_material = R"(Basic {
  //   $Diffuse = "test.png";
  // })";

  //   kfx::MaterialParser parser;
  //   std::istringstream stream(test_material);
  //   parser.parse(stream);

  kfx::Window window(640, 480, "basic example");

  MyTest my_test(window);
  my_test.init();

  window.setClearColor(0.f, 0.f, 0.f);

  kfx::Clock clock;
  while (window.isOpen()) {
    double dt = clock.reset();

    my_test.update(static_cast<float>(dt));
    my_test.render();

    static int counter = 0;
    if (counter++ == 60) {
      std::cout << 1.0 / dt << std::endl;
      counter = 0;
    }
  }

  std::cin.ignore();
  std::cin.get();

  return 0;
}
