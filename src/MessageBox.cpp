#include "kfx/MessageBox.h"

#include "kfx/Message.h"

#include <algorithm>

namespace kfx {
void MessageBox::registerListener(ListenerInterface* listener,
                                  Message::Type type) {
  // If the listener already exists in this category, ignore the request...
  for (auto registered_listener : m_registered_listeners[type]) {
    if (listener == registered_listener) {
      return;
    }
  }

  // Otherwise, add it to the category
  m_registered_listeners[type].push_back(listener);
}

void MessageBox::unregisterListener(ListenerInterface* listener) {
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

void MessageBox::postMessage(Message message) { m_message_queue.push(message); }

void MessageBox::distributeMessages() {
  while (!m_message_queue.empty()) {
    Message current_message = m_message_queue.front();
    m_message_queue.pop();

    for (auto registered_listener :
         m_registered_listeners[current_message.type]) {
      registered_listener->tell(current_message);
    }
  }
}
}