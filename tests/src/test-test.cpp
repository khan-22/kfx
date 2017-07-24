#include <Catch/catch.hpp>

TEST_CASE("Tests are active", "[Catch]") {
  bool foo = true;

  REQUIRE(foo == true);
}