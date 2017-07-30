#include <kfx/Assert.h>

#include <sstream>

namespace kfx {
KfxAssertFailure::KfxAssertFailure(const char* condition, const char* file,
                                   int line)
    : std::runtime_error(std::string("An assertion failed!") +
                         std::string("\n-> Condition: ") + condition +
                         std::string("\n-> File: ") + file +
                         std::string("\n-> Line: ") + std::to_string(line)) {}

KfxContractFailure::KfxContractFailure(const char* condition, const char* file,
                                       int line)
    : std::runtime_error(std::string("A contract failed!") +
                         std::string("\n-> Condition: ") + condition +
                         std::string("\n-> File: ") + file +
                         std::string("\n-> Line: ") + std::to_string(line)) {}

KfxAbortFailure::KfxAbortFailure(const char* file, int line)
    : std::runtime_error(std::string("Process aborted!") +
                         std::string("\n-> File: ") + file +
                         std::string("\n-> Line: ") + std::to_string(line)) {}
}
