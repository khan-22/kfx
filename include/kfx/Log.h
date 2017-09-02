/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#include "kfx/resources/FileUtil.h"

namespace kfx {
namespace detail {
template <typename... TArgs>
void log(TArgs... t) {
  (std::cout << ... << t) << '\n';
}

template <typename... TArgs>
void log_error(TArgs... t) {
  (std::cerr << ... << t) << '\n';
}
}
}

#define LOG(...) kfx::detail::log(__VA_ARGS__);

#define LOG_ERROR(...)                                              \
  kfx::detail::log_error(kfx::util::breakDownPath(__FILE__).back(), \
                         " @ Line ", __LINE__, "\n---> ERROR: ", __VA_ARGS__);

#endif  // LOG_H
