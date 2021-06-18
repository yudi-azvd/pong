#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <iostream>


class Ball {
public:
  float radius = 10;

  float x;

  float y;

  float direction;

  bool canMove = false;
  
  float step = 0.25;

  Ball();

  ~Ball();

  void move();

private:

};


#endif // BALL_H_INCLUDED