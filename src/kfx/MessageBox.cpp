#include "kfx/MessageBox.h"

#include "kfx/EventListener.h"
#include "kfx/StandardEventMessage.h"

#include <algorithm>

namespace kfx {
void MessageBox::unregisterListener(EventListener* listener) {
  for (auto& listener_category : m_registered_listeners) {
    auto it =
        std::find(listener_category.begin(), listener_category.end(), listener);
    while (it != listener_category.end()) {
      listener_category.erase(it);
      it = std::find(listener_category.begin(), listener_category.end(),
                     listener);
    }
  }
}

void MessageBox::postMessage(Message& message) {
  m_message_queue.push(message);
}

void MessageBox::distributeMessages() {
  while (!m_message_queue.empty()) {
    Message& current_message = m_message_queue.front();

    for (auto registered_listener :
         m_registered_listeners[current_message.index()]) {
      registered_listener->tell(current_message);
    }

    m_message_queue.pop();
  }
}
}