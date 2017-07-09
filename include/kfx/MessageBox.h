/*************************/
/* (C) Karl Hansson 2017 */
/*************************/

#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

namespace kfx {

class MessageBox {
 public:
  MessageBox();
  ~MessageBox();

  void registerListener();
  void postMessage();
  void distributeMessages();

 private:
};

class MessageBox;
}

#endif  // MESSAGE_BOX_H
