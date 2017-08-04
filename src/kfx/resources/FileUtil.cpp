#include "kfx/resources/FileUtil.h"

#include <algorithm>
#include <cctype>
#include "kfx/Assert.h"

#include <iostream>
namespace kfx {
namespace util {
std::vector<std::string> breakDownPath(std::string path) {
  std::vector<std::string> path_broken;

  std::istringstream string_stream(path);

// Test if the string is a valid path
  bool is_valid = true;
  for (auto it = path.begin(); it != path.end(); it++) {
    if (std::isspace(*it) != 0) {
      is_valid = false;
    }
  }
  kfx_contract(is_valid == true);

  std::string token;
  while (std::getline(string_stream, token, '/')) {
    path_broken.push_back(token);
  }

  // size_t pos = 0;
  // size_t pos_next;
  // while ((pos_next = path.find("/", pos)) != std::string::npos) {
  //   path_broken.push_back(path.substr(pos, pos_next));
  //   pos = pos_next;
  // }

  // // If there were no delimiters ("/"), push the whole path,
  // // since it probably was just a single entry anyway.
  // if (path_broken.empty() == true) {
  //   path_broken.push_back(path);
  // }

  return path_broken;
}

std::stringstream loadFileIntoStream(std::string path) {
  std::stringstream string_stream;

  std::ifstream input_stream(path);
  // kfx_contract(input_stream.is_open());

  if (input_stream.is_open()) {
    string_stream << input_stream.rdbuf();
    input_stream.close();
  }

  return string_stream;
}
}
}