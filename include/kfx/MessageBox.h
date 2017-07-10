/*************************/
/* (C) Karl Hansson 2017 */
/*************************/

#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include "kfx/ListenerInterface.h"
#include "kfx/Message.h"

#include <array>
#include <queue>
#include <vector>

namespace kfx {
class MessageBox {
 public:
  // Register a listener object for a specific type of message
  void registerListener(ListenerInterface* listener, Message::Type type);

  // Unregister a listener object for all types of messages
  void unregisterListener(ListenerInterface* listener);

  // Post a message to the queue
  void postMessage(Message message);

  // Empty the queue by distributing the messages to all relevant parties
  void distributeMessages();

 private:
  std::queue<Message> m_message_queue;

  std::array<std::vector<ListenerInterface*>, Message::Type::NUM_TYPES>
      m_registered_listeners;
};
}

#endif  // MESSAGE_BOX_H
