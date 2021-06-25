#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#include "player.h"
#include "ball.h"
#include "command.h"
#include "lastframeclock.h"


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

  void restartBall();
  
  void movePlayer(MovePlayerCommand command);
  
  void moveBall();
  
  void moveBallWithMouse(float x, float y);
  
  void render();

private:
  const float sideOffset = 40;

  float playerStep = 1;

  float randomDirectionForBall();
};


#endif // GAME_H_INCLUDED