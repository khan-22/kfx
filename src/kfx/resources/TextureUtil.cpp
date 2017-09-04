#include "kfx/resources/TextureUtil.h"

#include <GL/glew.h>
#include <lodepng/lodepng.h>

#include "kfx/Assert.h"

namespace kfx {
namespace util {
std::optional<Image> loadImage(fs::path path) {
  if (fs::exists(path)) {
    Image image;
    unsigned error =
        lodepng::decode(image.data, image.width, image.height, path.c_str());

    kfx_contract(error == 0);

    return image;
  } else {
    return {};
  }
}
}
}
