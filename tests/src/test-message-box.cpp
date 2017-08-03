/***********************************/
/* Test: message-box         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/EventListener.h>
#include <kfx/MessageBox.h>

namespace kfx {
class TestListener : public kfx::EventListener {
 public:
  TestListener(MessageBox& message_box)
      : EventListener(message_box), m_counter(0) {
    m_message_box.registerListener(this, StandardEventMessage::TEST1);
  }
  ~TestListener() override { m_message_box.unregisterListener(this); };

  void tell(MessageArgument& message) final override {
    auto* data = reinterpret_cast<
        kfx::EventArgumentData<kfx::StandardEventMessage::TEST1>*>(
        message.data.get());

    if (data->message == "...") ++m_counter;
  }

  uint32_t getCounter() const { return m_counter; }

 private:
  uint32_t m_counter;
};
}

SCENARIO("Sending messages over a message box", "[message]") {
  kfx::MessageBox message_box;

  GIVEN("A debug message listener") {
    kfx::MessageArgument debug_message(kfx::StandardEventMessage::TEST1);
    auto* data = reinterpret_cast<
        kfx::EventArgumentData<kfx::StandardEventMessage::TEST1>*>(
        debug_message.data.get());

    data->message = "...";

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
      kfx::MessageArgument test_message(kfx::StandardEventMessage::TEST2);
      auto* data = reinterpret_cast<
          kfx::EventArgumentData<kfx::StandardEventMessage::TEST2>*>(
          test_message.data.get());

      data->message = "...";

      REQUIRE(test_listener.getCounter() == 0);
      message_box.postMessage(test_message);
      message_box.distributeMessages();
      THEN("the listener is not notified") {
        REQUIRE(test_listener.getCounter() == 0);
      }
    }
  }
}
