#include "kfx/system/System.h"

namespace kfx {
System::System(GameObjectFactory& game_object_factory)
    : m_game_object_factory(game_object_factory) {
  // ...
}

System::~System() {
  // ...
}
}
