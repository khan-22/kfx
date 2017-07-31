/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef OBSERVER_INTERFACE_H
#define OBSERVER_INTERFACE_H

#include <vector>

namespace kfx {

struct ObserverArgument {
  uint32_t type;
  void* data;
};

class ObserverInterface {
 public:
  virtual void onNotify(ObserverArgument arg) = 0;

 private:
};
}
#endif  // OBSERVER_INTERFACE_H
