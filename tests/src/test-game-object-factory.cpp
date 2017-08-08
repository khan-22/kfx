/***********************************/
/* Test: game-object-factory         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Assert.h>
#include <kfx/GameObjectFactory.h>

// Test implementation of GameObjectFactory which can create our specific
// unit-test object
namespace kfx {
class TestFactory : public GameObjectFactory {
 public:
  TestFactory(MeshManager& mesh_manager, ShaderManager& shader_manager,
              TextureManager& texture_manager)
      : GameObjectFactory(mesh_manager, shader_manager, texture_manager) {}

  Handle createUnitTestObject() {
    // ...
    Handle object_handle = m_game_objects.addResourceEntry();
    // Handle transform_component_handle =
    //     addComponent(object_handle, ComponentType::TRANSFORM);

    return object_handle;
  }

 private:
};
}

SCENARIO("Creating a test object", "[factory]") {
  GIVEN("A(n implementation of) GameObjectFactory") {
    kfx::MeshManager mesh_manager;
    kfx::ShaderManager shader_manager;
    kfx::TextureManager texture_manager;
    kfx::TestFactory factory =
        kfx::TestFactory(mesh_manager, shader_manager, texture_manager);
    WHEN("creating a unit test object") {
      kfx::Handle handle = factory.createUnitTestObject();

      THEN("a valid handle to the object is returned") {
        REQUIRE(handle != kfx::Handle::NULL_HANDLE);

        kfx::HandledResource<kfx::GameObject>& objects =
            factory.getGameObjects();

        REQUIRE_NOTHROW(objects.getResourceEntry(handle));
      }

      AND_WHEN("adding a transform component to it") {
        kfx::GameObject* object =
            factory.getGameObjects().getResourceEntry(handle);
        REQUIRE(object->hasComponent(kfx::ComponentType::TRANSFORM) == false);

        kfx::Handle transform_component =
            factory.addComponent(handle, kfx::ComponentType::TRANSFORM);

        THEN("a valid handle is returned") {
          REQUIRE(handle != kfx::Handle::NULL_HANDLE);

          REQUIRE(object->hasComponent(kfx::ComponentType::TRANSFORM) == true);

          AND_THEN(
              "the component is added to the array of transform components") {
            REQUIRE(factory.getTransformComponents().resource.size() == 1);
          }
        }

        AND_WHEN("removing the transform component") {
          factory.removeComponent(handle, kfx::ComponentType::TRANSFORM);
          THEN("the component handle is made invalid") {
            REQUIRE(object->hasComponent(kfx::ComponentType::TRANSFORM) ==
                    false);
            REQUIRE_THROWS_AS(factory.getTransformComponents().getResourceEntry(
                                  transform_component),
                              kfx::KfxContractFailure);
            AND_THEN(
                "the component is removed from the array of transform "
                "components") {
              REQUIRE(factory.getTransformComponents().resource.size() == 0);
            }
          }
        }
      }
    }
  }
}
