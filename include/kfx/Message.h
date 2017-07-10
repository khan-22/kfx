/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace kfx {
struct Message {
 public:
  enum Type { DEBUG, TEST, KEY_INPUT, MOUSE_MOVE, MOUSE_INPUT, NUM_TYPES };

 public:
  // Debug Ctor (Is this a good idea?)
  Message(Type type);

  static Message makeDebugMessage(std::string msg);
  static Message makeTestMessage(int x, int y, int z);
  static Message makeKeyInputMessage(int action, int key, int mods);
  static Message makeMouseMoveMessage(double x, double y);
  static Message makeMouseInputMessage(int action, int button, int mods);

  Type type;

  union {
    // Debug message
    struct {
      char debug_msg[80];
    };

    // Test message
    struct {
      int test_x, test_y, test_z;
    };

    // Key Input message
    struct {
      int key_input_action;
      int key_input_key;
      int key_input_mods;
    };

    // Mouse Move message
    struct {
      double mouse_move_x;
      double mouse_move_y;
    };

    // Mouse Input message
    struct {
      int mouse_input_action;
      int mouse_input_button;
      int mouse_input_mods;
    };
  };
};
}

#endif  // MESSAGE_H
