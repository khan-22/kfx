/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef KFX_ASSERT_H
#define KFX_ASSERT_H

#include <stdexcept>

namespace kfx {
class KfxAssertFailure final : public std::runtime_error {
 public:
  KfxAssertFailure(const char* condition, const char* file, int line);
};

class KfxContractFailure final : public std::runtime_error {
 public:
  KfxContractFailure(const char* condition, const char* file, int line);
};

class KfxAbortFailure final : public std::runtime_error {
 public:
  KfxAbortFailure(const char* file, int line);
};
}

#ifndef NDEBUG
#define kfx_assert(condition)                                         \
  (!(condition))                                                      \
      ? throw kfx::KfxAssertFailure((#condition), __FILE__, __LINE__) \
      : (void)0
#else
#define kfx_assert(condition) (void)0
#endif  // NDEBUG

#define kfx_contract(condition)                                         \
  (!(condition))                                                        \
      ? throw kfx::KfxContractFailure((#condition), __FILE__, __LINE__) \
      : (void)0

#define kfx_abort() throw kfx::KfxAbortFailure(__FILE__, __LINE__);

#endif  // KFX_ASSERT_H
