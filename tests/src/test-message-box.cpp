/***********************************/
/* Test: message-box         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/EventListener.h>
#include <kfx/MessageBox.h>
#include <kfx/StandardEventMessage.h>

namespace kfx {
class TestListener : public kfx::EventListener {
 public:
  TestListener(MessageBox& message_box)
      : EventListener(message_box), m_counter(0) {
    m_message_box.registerListener<Test1>(this);
  }
  ~TestListener() override { m_message_box.unregisterListener(this); };

  void tell(Message& msg) final override {
    if (auto data = std::get_if<Test1>(&msg)) {
      if (data->message == "...") ++m_counter;
    }
  }

  uint32_t getCounter() const { return m_counter; }

 private:
  uint32_t m_counter;
};
}

SCENARIO("Sending messages over a message box", "[message]") {
  kfx::MessageBox message_box;

  GIVEN("A debug message listener") {
    kfx::Message debug_message = kfx::Test1{"..."};

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
      kfx::Message test_message = kfx::Test2{"..."};

      REQUIRE(test_listener.getCounter() == 0);
      message_box.postMessage(test_message);
      message_box.distributeMessages();
      THEN("the listener is not notified") {
        REQUIRE(test_listener.getCounter() == 0);
      }
    }
  }
}
