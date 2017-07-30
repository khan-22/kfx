/***********************************/
/* Test: message-box         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/Listener.h>
#include <kfx/MessageBox.h>

namespace kfx {
class TestListener : public kfx::Listener {
 public:
  TestListener(MessageBox &message_box) : Listener(message_box), m_counter(0) {
    m_message_box.registerListener(this, Message::DEBUG);
  }
  ~TestListener() override { m_message_box.unregisterListener(this); };

  void tell(Message message) final override { ++m_counter; }

  uint32_t getCounter() const { return m_counter; }

 private:
  uint32_t m_counter;
};
}

SCENARIO("Sending messages over a message box", "[message]") {
  kfx::MessageBox message_box;

  GIVEN("A debug message listener") {
    kfx::Message debug_message = kfx::Message::makeDebugMessage("...");
    kfx::TestListener test_listener(message_box);
    WHEN("sending a debug message") {
      REQUIRE(test_listener.getCounter() == 0);
      message_box.postMessage(debug_message);
      message_box.distributeMessages();
      THEN("the listener is notified") {
        REQUIRE(test_listener.getCounter() == 1);
      }
    }

    WHEN("sending a non-debug message") {
      kfx::Message test_message = kfx::Message::makeTestMessage(1, 2, 3);
      REQUIRE(test_listener.getCounter() == 0);
      message_box.postMessage(test_message);
      message_box.distributeMessages();
      THEN("the listener is not notified") {
        REQUIRE(test_listener.getCounter() == 0);
      }
    }
  }
}
