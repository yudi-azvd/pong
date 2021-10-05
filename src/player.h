#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "lastframeclock.h"


class Player {
public:
  uint8_t id;
  int points = 0;
  const float width = 10;
  const float height = 90;
  float x;
  float y;
  float stepsPerSecond = 1000.0;

  sf::Font font;
  sf::Text text;

  Player();
  
  ~Player();

  void move(float dy);

  void update();

  void render(sf::RenderTarget* target);

private:
  sf::RectangleShape rectangle;
};


#endif // PLAYER_H_INCLUDED