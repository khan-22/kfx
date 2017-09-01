/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

namespace kfx {
namespace detail {

extern FILE* log_file;

void beginLogging();

template <typename... MArgs>
void log(const char* file, int line, const char* format, MArgs... mArgs) {
  printf(format, std::forward<MArgs>(mArgs)...);
  fprintf(log_file, format, std::forward<MArgs>(mArgs)...);
}

void finishLogging();
}
}

#define START_LOG() detail::beginLogging();

#define LOG(fmt, ...) detail::log(__FILE__, __LINE__, fmt "\n", __VA_ARGS__);
#define LOG_ERROR(fmt, ...) \
  detail::log(__FILE__, __LINE__, "ERROR: " fmt "\n", __VA_ARGS__);

#define FINISH_LOG() detail::finishLogging();

#endif  // LOG_H
