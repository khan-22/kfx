/***********************************/
/* Test: window         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Window.h>

SCENARIO("Opening and closing a window", "[window]") {
  GIVEN("a window") {
    kfx::Window window(100, 140, "test");
    REQUIRE(window.getWidth() == 100);
    REQUIRE(window.getHeight() == 140);
    REQUIRE(window.getTitle() == "test");

    WHEN("calling close") {
      REQUIRE(window.isOpen() == true);
      window.close();
      THEN("it is no longer open") {
        REQUIRE(window.isOpen() == false);  //
      }
    }
  }
}
