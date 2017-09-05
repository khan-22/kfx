/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

namespace kfx {
struct Image {
  std::vector<uint8_t> data;

  uint32_t width;
  uint32_t height;
};
}
#endif  // IMAGE_H
