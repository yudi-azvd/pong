#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <iostream>

#include <SFML/Graphics.hpp>


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

  void update();

  void move();

  void render(sf::RenderWindow* window);

private:
  sf::CircleShape circle;
};


#endif // BALL_H_INCLUDED