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
struct MessageArgument;
class EventListener;

class MessageBox {
 public:
  // Register a listener object for a specific type of message
  void registerListener(EventListener* listener,
                        StandardEventMessage::Type type);

  // Unregister a listener object for all types of messages
  void unregisterListener(EventListener* listener);

  // Post a message to the queue
  void postMessage(MessageArgument& message);

  // Empty the queue by distributing the messages to all relevant parties
  void distributeMessages();

 private:
  std::queue<MessageArgument> m_message_queue;

  std::array<std::vector<EventListener*>, StandardEventMessage::NUM_TYPES>
      m_registered_listeners;
};
}

#endif  // MESSAGE_BOX_H
