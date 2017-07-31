/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef OBSERVABLE_SUBJECT_H
#define OBSERVABLE_SUBJECT_H

#include <vector>

#include "kfx/ObserverInterface.h"

namespace kfx {
class ObservableSubject {
 public:
  void addObserver(ObserverInterface* observer);
  void removeObserver(ObserverInterface* observer);
  void notify(ObserverArgument arg);

 private:
  std::vector<ObserverInterface*> m_observers;
};
}
#endif  // OBSERVABLE_SUBJECT_H
