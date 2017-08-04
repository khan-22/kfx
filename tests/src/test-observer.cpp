/***********************************/
/* Test: observer         */
/* By: Karl Hansson 2017           */
/***********************************/

#include <Catch/catch.hpp>

#include <kfx/ObservableSubject.h>
#include <kfx/ObserverInterface.h>
#include <kfx/StandardObserverMessage.h>

namespace kfx {
class TestObserver : public ObserverInterface {
 public:
  void onNotify(ObserverArgument arg) final override {
    switch (arg.type) {
      case StandardObserverMessage::TEST1: {
        auto data =
            static_cast<ObserverArgumentData<StandardObserverMessage::TEST1>*>(
                arg.data);
        m_counter += data->a;
        break;
      }
      case StandardObserverMessage::TEST2: {
        auto data =
            static_cast<ObserverArgumentData<StandardObserverMessage::TEST2>*>(
                arg.data);
        m_counter += data->a + data->b;
        break;
      }
      default:
        break;
    }
  }

  int getCounter() const { return m_counter; }

 private:
  int m_counter = 0;
};

class TestSubject : public ObservableSubject {
 public:
  void doTest1() {
    ObserverArgument arg;
    arg.type = StandardObserverMessage::TEST1;

    ObserverArgumentData<StandardObserverMessage::TEST1> data;
    data.a = 1;

    arg.data = &data;

    notify(arg);
  }

  void doTest2() {
    ObserverArgument arg;
    arg.type = StandardObserverMessage::TEST2;

    ObserverArgumentData<StandardObserverMessage::TEST2> data;
    data.a = 1;
    data.b = 1;

    arg.data = &data;

    notify(arg);
  }

 private:
};
}

SCENARIO("Sending messages through observers and subjects", "[observer]") {
  GIVEN("An observer and a subject") {
    kfx::TestObserver observer;
    REQUIRE(observer.getCounter() == 0);
    kfx::TestSubject subject;
    subject.addObserver(&observer);

    WHEN("a TEST1 message is sent") {
      subject.doTest1();
      THEN("the observer is notified") { REQUIRE(observer.getCounter() == 1); }
    }

    WHEN("a TEST2 message is sent") {
      subject.doTest2();
      THEN("the observer is notified") { REQUIRE(observer.getCounter() == 2); }
    }

    WHEN("the observer is removed from the subject") {
      subject.removeObserver(&observer);

      AND_WHEN("a TEST1 message is sent") {
        subject.doTest1();
        THEN("the observer is not notified") {
          REQUIRE(observer.getCounter() == 0);
        }
      }

      AND_WHEN("a TEST2 message is sent") {
        subject.doTest2();
        THEN("the observer is not notified") {
          REQUIRE(observer.getCounter() == 0);
        }
      }

      AND_WHEN("attempting to remove an observer twice") {
        THEN("nothing happens") {
          REQUIRE_NOTHROW(subject.removeObserver(&observer));
        }
      }
    }
  }
}
