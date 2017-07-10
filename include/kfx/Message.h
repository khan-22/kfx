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
  enum Type { DEBUG, TEST, NUM_TYPES };

 public:
  // Debug Ctor (Is this a good idea?)
  Message(Type type);

  static Message makeDebugMessage(std::string msg);
  static Message makeTestMessage(int x, int y, int z);

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

    //
  };
};
}

#endif  // MESSAGE_H
