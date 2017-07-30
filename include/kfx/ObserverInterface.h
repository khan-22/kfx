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
<<<<<<< HEAD
=======

  bool containsData() { return data != nullptr; }
>>>>>>> 5e208c023b0609bf2cc0125c49693fa640a5de73
};

class ObserverInterface {
 public:
  virtual void notify(ObserverArgument arg) = 0;

 private:
};
}
#endif  // OBSERVER_INTERFACE_H
