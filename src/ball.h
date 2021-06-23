#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <math.h>
#include <SFML/Graphics.hpp>


class Ball {
public:
  float radius = 10;
  float step = 0.25;
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

  void render(sf::RenderTarget* target);

private:
  sf::CircleShape circle;
};


#endif // BALL_H_INCLUDED