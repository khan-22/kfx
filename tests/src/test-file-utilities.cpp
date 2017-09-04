/***********************************/
/* Test: file-utilities         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Assert.h>
#include <kfx/resources/FileUtil.h>

#include <string>

// SCENARIO("Function breakDownPath(string) breaks file paths into separate
// parts",
//          "[util]") {
//   GIVEN("A relative path to some file") {
//     std::string path("this/is/a/relative/path");

//     WHEN("the path is broken down") {
//       auto broken_down_path = kfx::util::breakDownPath(path);

//       THEN("the pieces correspond to the original path") {
//         REQUIRE(broken_down_path[0] == "this");
//         REQUIRE(broken_down_path[1] == "is");
//         REQUIRE(broken_down_path[2] == "a");
//         REQUIRE(broken_down_path[3] == "relative");
//         REQUIRE(broken_down_path[4] == "path");
//       }
//     }
//   }

//   GIVEN("An absolute path to some file") {
//     std::string path("/this/is/an/absolute/path");

//     WHEN("the path is broken down") {
//       auto broken_down_path = kfx::util::breakDownPath(path);

//       THEN(
//           "the pieces correspond to the original path and the first piece is
//           "
//           "empty") {
//         REQUIRE(broken_down_path[0] == "");
//         REQUIRE(broken_down_path[1] == "this");
//         REQUIRE(broken_down_path[2] == "is");
//         REQUIRE(broken_down_path[3] == "an");
//         REQUIRE(broken_down_path[4] == "absolute");
//         REQUIRE(broken_down_path[5] == "path");
//       }
//     }
//   }

//   GIVEN("A non-conforming string") {
//     std::string not_a_path("hello errors! /What/ is/happening?");

//     WHEN("the string is broken down") {
//       THEN("the function should fail") {
//         REQUIRE_THROWS_AS(kfx::util::breakDownPath(not_a_path),
//                           kfx::KfxContractFailure);
//       }
//     }
//   }
// }

SCENARIO(
    "Function loadFileIntoStream(string) loads the contents of a file into a "
    "string stream object",
    "[util]") {
  std::ofstream test_data("./test_data.txt");
  test_data << "hello world I am data" << std::endl;
  test_data.close();

  GIVEN("A relative path to some file") {
    std::string path("./test_data.txt");
    WHEN("the file is loaded") {
      auto string_stream = kfx::util::loadFileIntoStream(path);
      THEN("a valid string stream object is returned") {
        std::string temp;
        string_stream >> temp;
        REQUIRE(temp == "hello");
        string_stream >> temp;
        REQUIRE(temp == "world");
        string_stream >> temp;
        REQUIRE(temp == "I");
        string_stream >> temp;
        REQUIRE(temp == "am");
        string_stream >> temp;
        REQUIRE(temp == "data");
      }
    }
  }

  // GIVEN("A non-conforming string") {
  //   std::string not_a_path("hello errors! /What/ is/happening?");

  //   WHEN("the string is passed to the function") {
  //     THEN("the function should fail") {
  //       REQUIRE_THROWS_AS(kfx::util::loadFileIntoStream(not_a_path),
  //                         kfx::KfxContractFailure);
  //     }
  //   }
  // }
}