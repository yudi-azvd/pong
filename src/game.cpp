#include "game.h"

Game::Game() {
  srand(time(NULL));

  float initialDirection = rand() % 2 ? 0 : 180;
  ball.direction = initialDirection;
  ball.y = windowHeight/2;
  ball.x = windowWidth/2;

  player1.id = 1;
  player1.x = sideOffset;
  player1.y = windowHeight/2;

  player2.id = 2;
  player2.x = windowWidth - sideOffset;
  player2.y = windowHeight/2;
}


Game::~Game() {}


void Game::update() {
  // ball.move();
  moveBall();
}


void Game::start() {
  ball.canMove = true;
}


void Game::movePlayer(MovePlayerCommand command) {
  Player& player = command.playerId == 1 ? player1 : player2;
  int direction = command.upDirection ? -1 : 1;

  bool isAlmostTouchingCeiling = player.y-player.height/2 <= playerStep;
  if (isAlmostTouchingCeiling && command.upDirection) {
    return;
  }

  bool isAlmostTouchingFloor = std::abs(player.y+player.height/2 - windowHeight) <= playerStep;
  if (isAlmostTouchingFloor && !command.upDirection) {
    return;
  }

  player.y += direction*playerStep;
}


void Game::setPlayerMovement(int playerId, float dy) {
  Player& player = playerId == 1 ? player1 : player2;
  int direction = dy < 0 ? -1 : 1;

  bool isAlmostTouchingCeiling = player.y-player.height/2 <= playerStep;
  if (isAlmostTouchingCeiling && direction < 0) {
    return;
  }

  bool isAlmostTouchingFloor = std::abs(player.y+player.height/2 - windowHeight) <= playerStep;
  if (isAlmostTouchingFloor && direction > 0) {
    return;
  }

  player.y += direction*playerStep;
}



void Game::moveBall() {
  ball.move();
  if (!ball.canMove)
    return;

  float rad = ball.direction/180*M_PI;
  float xStep = cos(rad)*ball.step;
  float yStep = sin(rad)*ball.step;

  bool isAlmostTouchingCeiling = ball.y-ball.radius/2 <= ball.step;
  if (isAlmostTouchingCeiling && yStep < 0) {
    return;
  }

  bool isAlmostTouchingRightSide = windowWidth - (ball.x+ball.radius/2) <= ball.step;
  if (isAlmostTouchingRightSide && xStep > 0) {
    return;
  }

  bool isAlmostTouchingLeftSide = ball.x-ball.radius/2 <= ball.step;
  if (isAlmostTouchingLeftSide && xStep < 0) {
    return;
  }

  ball.x += xStep;
  ball.y += yStep;
}
