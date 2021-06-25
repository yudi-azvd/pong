#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <math.h>
#include <SFML/Graphics.hpp>

#include "lastframeclock.h"


class Ball {
public:
  float radius = 10;
  float stepsPerSecond = 3*360;
  float x;
  float y;
  float direction; // Em graus
  float directionInRadians;
  const float degreesToRadians = M_PI/180;
  const float radiansToDegrees = 180/M_PI;
  bool canMove = false;

  Ball();

  ~Ball();

  void setDirection(float direction);

  void update();

  void move();

  void bounce(std::string newDirection);

  void render(sf::RenderTarget* target);

private:
  sf::CircleShape circle;
};


#endif // BALL_H_INCLUDED