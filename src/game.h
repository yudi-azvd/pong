#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "player.h"
#include "ball.h"
#include "command.h"


class Game {
public:
  std::string title = "Pong";

  sf::RenderWindow* window;
  
  float windowHeight = 560;
  
  float windowWidth = 720;

  Player player1;
  
  Player player2;

  Ball ball;

  Game(sf::RenderWindow* window);

  ~Game();

  void update();

  void start();

  void movePlayer(MovePlayerCommand command);
  
  void moveBall();
  
  void render();

private:
  const float sideOffset = 40;

  float playerStep = 0.5;
};


#endif // GAME_H_INCLUDED