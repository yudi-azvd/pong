#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <math.h>
#include <SFML/Graphics.hpp>

#include "lastframeclock.h"


class Ball {
public:
  float radius = 10;
  float stepsPerSecond = 360;
  float x;
  float y;
  float direction; // Em graus
  float directionInRadians;
  const float degreesToRadians = M_PI/180;
  bool canMove = false;

  Ball();

  ~Ball();

  void setDirection(float direction);

  void update();

  void move();

  void bounce();

  void render(sf::RenderTarget* target);

private:
  sf::CircleShape circle;

  struct MainDirection {
    bool up;
    bool left;
    bool down;
    bool right;
  };

  MainDirection getMainDirection(float xComponent, float yComponent);
};


#endif // BALL_H_INCLUDED