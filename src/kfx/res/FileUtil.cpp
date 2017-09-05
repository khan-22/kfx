#include "kfx/res/FileUtil.h"

#include <algorithm>
#include <cctype>
#include "kfx/Assert.h"

#include <iostream>
namespace kfx {
namespace util {

std::stringstream loadFileIntoStream(fs::path path) {
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
