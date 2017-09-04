/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace kfx {
namespace util {
std::stringstream loadFileIntoStream(fs::path path);
}
}

#endif  // FILE_UTIL_H
