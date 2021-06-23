#include "game.h"


Game::Game(sf::RenderWindow* w) {
  srand(time(NULL));

  window = w;
  window->create(
    sf::VideoMode(windowWidth, windowHeight), 
    title, 
    sf::Style::Close | sf::Style::Titlebar);

  ball.setDirection(randomDirectionForBall());
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
  moveBall();
  ball.update();
  player1.update();
  player2.update();
}


void Game::restartBall() {
  ball.setDirection(randomDirectionForBall());
  ball.y = windowHeight/2;
  ball.x = windowWidth/2;
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

  player.move(direction*playerStep);
}


void Game::moveBall() {
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

  ball.move();
}


void Game::render() {
  window->clear();
  player1.render(window);
  player2.render(window);
  ball.render(window);
  window->display();
}


float Game::randomDirectionForBall() {
  float initialDirection = rand() % 2 ? 0 : 180;
  initialDirection = rand() % 360;
  return initialDirection;
}

