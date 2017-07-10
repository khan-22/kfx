/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

namespace kfx {
struct Message {
 public:
  enum Type { DEBUG, NUM_TYPES };

 public:
  // Debug Ctor (Is this a good idea?)
  Message(Type type);

  Type type;

  union {
    // Debug message
    struct {
      char debug_msg[80];
    };

    //
  };
};
}

#endif  // MESSAGE_H
