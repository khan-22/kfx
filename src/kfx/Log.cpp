#include "kfx/Log.h"

#include <stdlib.h>

namespace kfx {
namespace detail {
extern FILE* log_file;

void beginLogging() {
  log_file = fopen("log.txt", "w");
  if (!log_file) {
    printf("FAILURE TO OPEN LOG FILE!");
    abort();
  }
}
void finishLogging() { fclose(log_file); }
}
}