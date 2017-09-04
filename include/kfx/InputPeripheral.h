/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef INPUT_PERIPHERAL_H
#define INPUT_PERIPHERAL_H

#include "kfx/EventListener.h"
#include "kfx/MessageBox.h"

namespace kfx {
class InputPeripheral {
 public:
  InputPeripheral(MessageBox& message_box) : m_message_box(message_box) {}
  virtual ~InputPeripheral() = default;

 protected:
  MessageBox& m_message_box;
};
}
#endif  // INPUT_PERIPHERAL_H
