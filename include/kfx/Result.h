/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef RESULT_H
#define RESULT_H

#include <utility>

namespace kfx {
enum KfxStatus { FAILURE, SUCCESS };

template <typename T>
using KfxResult = std::pair<T, KfxStatus>;
}

#endif  // RESULT_H
