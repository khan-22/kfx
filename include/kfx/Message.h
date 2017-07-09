/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace kfx {
class Message {
 public:
  enum Type { DEBUG, NUM_TYPES };

 public:
  Message(Type type);

  Type getType();

 private:
  Type m_type;

  union {
    // Debug message
    struct {
      std::string msg;
    };
  };
};
}

#endif  // MESSAGE_H
