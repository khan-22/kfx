#include "kfx/ObservableSubject.h"

#include <algorithm>

namespace kfx {
void ObservableSubject::addObserver(ObserverInterface* observer) {
  if (std::find(m_observers.begin(), m_observers.end(), observer) !=
      m_observers.end()) {
    m_observers.push_back(observer);
  }
}

void ObservableSubject::removeObserver(ObserverInterface* observer) {
  auto it = std::find(m_observers.begin(), m_observers.end(), observer);
  if (it != m_observers.end()) {
    m_observers.erase(it);
  }
}

void ObservableSubject::notify(ObserverArgument arg) {
  for (auto& observer : m_observers) {
    observer->onNotify(arg);
  }
}
}
