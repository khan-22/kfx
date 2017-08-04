/***********************************/
/* Test: handled_resource         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <vector>

#include <kfx/resources/HandledResource.h>

SCENARIO("Adding and removing from a HandledResource", "[resource]") {
  GIVEN("A handled resource") {
    kfx::HandledResource<int> handled_resource;

    WHEN("adding multiple entries (100)") {
      bool all_handles_valid = true;
      std::vector<kfx::Handle> handles;
      for (int i = 0; i < 100; i++) {
        kfx::Handle current_handle = handled_resource.addResourceEntry();
        handles.push_back(current_handle);
        if (current_handle == kfx::Handle::NULL_HANDLE) {
          all_handles_valid = false;
        } else {
          int* r = handled_resource.getResourceEntry(current_handle);
          *r = i;
        }
      }
      THEN("all handles are valid") {
        REQUIRE(all_handles_valid == true);
        for (int i = 0; i < 100; i++) {
          REQUIRE(*handled_resource.getResourceEntry(handles[i]) == i);
        }
      }

      AND_WHEN("some handles are removed") {
        for (int i = 50; i < 100; i++) {
          handled_resource.removeResourceEntry(handles[i]);
        }
        handles.resize(50);

        THEN("the rest remain valid") {
          for (int i = 0; i < 50; i++) {
            REQUIRE_NOTHROW(handled_resource.getResourceEntry(handles[i]));
            REQUIRE(*handled_resource.getResourceEntry(handles[i]) == i);
          }
        }

        AND_WHEN("adding many more handles (500)") {
          all_handles_valid = true;
          for (int i = 0; i < 500; i++) {
            kfx::Handle current_handle = handled_resource.addResourceEntry();
            handles.push_back(current_handle);
            if (current_handle == kfx::Handle::NULL_HANDLE) {
              all_handles_valid = false;
            } else {
              int* r = handled_resource.getResourceEntry(current_handle);
              *r = i;
            }
          }

          THEN("all handles are valid") {
            REQUIRE(all_handles_valid == true);
            for (int i = 0; i < 50; i++) {
              REQUIRE(*handled_resource.getResourceEntry(handles[i]) == i);
            }
            for (int i = 50; i < 550; i++) {
              REQUIRE(*handled_resource.getResourceEntry(handles[i]) == i - 50);
            }
          }
        }
      }
    }
  }
}
