#pragma once

#ifndef KEYBOARD_H
#define KEYBOARD_H

class MyClass
{
public:
  MyClass(int x, int y) : _x(x), _y(y) {};

  int calcArea();

private:
  int _x, _y;
};

int num_msg();

#endif //KEYBOARD_H
