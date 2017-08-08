/*************************/
/* (C) Karl Hansson 2017 */
/*************************/
#pragma once

#ifndef CLOCK_H
#define CLOCK_H

namespace kfx {
class Clock {
 public:
  Clock();

  double reset();
  double look();

 private:
  double m_previous_time;
};
}
#endif  // CLOCK_H
