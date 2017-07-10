#include "kfx/Message.h"

#include <cstring>

namespace kfx {
Message::Message(Type type) : type(type) {}

Message Message::makeDebugMessage(std::string msg) {
  Message message(Message::DEBUG);
  std::strncpy(message.debug_msg, msg.c_str(), 79);
  message.debug_msg[79] = '\0';
  return message;
}

Message Message::makeTestMessage(int x, int y, int z) {
  Message message(Message::TEST);
  message.test_x = x;
  message.test_y = y;
  message.test_z = z;
  return message;
}
}