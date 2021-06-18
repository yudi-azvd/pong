#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <random>
#include <functional>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "player.h"
#include "ball.h"
#include "moveplayercommand.h"


class Game {
public:
  float windowHeight = 560;
  
  float windowWidth = 720;

  Player player1;
  
  Player player2;

  Ball ball;

  Game();

  ~Game();

  void start();

  void movePlayer(MovePlayerCommand command);

  void moveBall();

private:
  const float sideOffset = 40;

  float playerStep = 4.0;

  // std::default_random_engine randGenerator;

  // std::uniform_real_distribution<float>() directionDistribuition();
};


#endif // GAME_H_INCLUDED