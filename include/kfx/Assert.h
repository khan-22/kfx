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
  KfxAssertFailure() : std::runtime_error("An assertion was hit!"){};
};
}

#ifndef NDEBUG
#define kfx_assert(condition) \
  (!(condition)) ? throw kfx::KfxAssertFailure() : (void)0
#else
#define kfx_assert(condition) (void)0
#endif  // NDEBUG

#endif  // KFX_ASSERT_H
