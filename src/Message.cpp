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

Message Message::makeKeyInputMessage(int action, int key, int mods) {
  Message message(Message::KEY_INPUT);
  message.key_input_action = action;
  message.key_input_key = key;
  message.key_input_mods = mods;
  return message;
}

Message Message::makeMouseMoveMessage(double x, double y) {
  Message message(Message::MOUSE_MOVE);
  message.mouse_move_x = x;
  message.mouse_move_y = y;
  return message;
}

Message Message::makeMouseInputMessage(int action, int button, int mods) {
  Message message(Message::MOUSE_INPUT);
  message.mouse_input_action = action;
  message.mouse_input_button = button;
  message.mouse_input_mods = mods;
  return message;
}
}