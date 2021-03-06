#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <math.h>
#include <SFML/Graphics.hpp>

#include "lastframeclock.h"


class Ball {
public:
  float size = 20;
  float stepsPerSecond = 1.5*360.0;
  // float stepsPerSecond = 1.5*360.0/8;
  float x;
  float y;
  float direction; // Em graus
  float directionInRadians;
  const float degreesToRadians = M_PI/180.0;
  const float radiansToDegrees = 180.0/M_PI;

  Ball();

  ~Ball();

  void setDirection(float direction);

  void update();

  void move();

  void bounce(std::string newDirection);

  void render(sf::RenderTarget* target);

private:
  sf::RectangleShape shape;
  sf::RectangleShape center;
};


#endif // BALL_H_INCLUDED