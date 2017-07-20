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

namespace kfx {
namespace util {
std::vector<std::string> breakDownPath(std::string path);

std::stringstream loadFileIntoStream(std::string path);
}
}

#endif  // FILE_UTIL_H
