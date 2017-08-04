#include <Catch/catch.hpp>

TEST_CASE("Tests are active", "[catch]") {
  bool foo = true;

  REQUIRE(foo == true);
}