/*************************/
/* (C) Karl Hansson 2017 */
/*************************/

#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

//#include "kfx/Listener.h"
#include "kfx/StandardEventMessage.h"

#include <array>
#include <memory>
#include <queue>
#include <vector>

namespace kfx {

// Forward declaration necessary to avoid cycle
class EventListener;

class MessageBox {
 public:
  // Register a listener object for a specific type of message
  template <typename T>
  void registerListener(EventListener* listener);

  // Unregister a listener object for all types of messages
  void unregisterListener(EventListener* listener);

  // Post a message to the queue
  void postMessage(Message& message);

  // Empty the queue by distributing the messages to all relevant parties
  void distributeMessages();

 private:
  std::queue<Message> m_message_queue;

  std::array<std::vector<EventListener*>, kfx::numberOfMessageTypes()>
      m_registered_listeners;

  template <typename T>
  std::size_t indexOf();
};

template <typename T>
void MessageBox::registerListener(EventListener* listener) {
  for (auto registered_listener : m_registered_listeners[indexOf<T>()]) {
    if (listener == registered_listener) {
      return;
    }
  }

  m_registered_listeners[indexOf<T>()].push_back(listener);
}

template <typename T>
std::size_t MessageBox::indexOf() {
  return (Message(T()).index());
}
}

#endif  // MESSAGE_BOX_H
