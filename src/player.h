#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <cstdint>

#include <SFML/Graphics.hpp>


class Player {
public:
  uint8_t id;
  int points = 0;
  const float width = 10;
  const float height = 90;
  float x;
  float y;

  Player();
  
  ~Player();

  void render();

private:

};


#endif // PLAYER_H_INCLUDED