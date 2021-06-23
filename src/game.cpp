#include "game.h"


Game::Game(sf::RenderWindow* w) {
  srand(time(NULL));

  window = w;
  window->create(
    sf::VideoMode(windowWidth, windowHeight), 
    title, 
    sf::Style::Close | sf::Style::Titlebar);
  window->setFramerateLimit(60);

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

  std::printf("player %d at (%3d, %3d)\n", player1.id, (int) player1.x, (int) player1.y);
  std::printf("player %d at (%3d, %3d)\n", player2.id, (int) player2.x, (int) player2.y);
  // std::printf("player %d at (%3d, %3d)\x1b[A\r", player2.id, (int) player2.x, (int) player2.y);
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
  float dx = cos(rad)*ball.step;
  float dy = sin(rad)*ball.step;
  float ballMinDistance = 6;

  bool isAlmostTouchingCeiling = ball.y-ball.radius/2 <= ballMinDistance;
  if (isAlmostTouchingCeiling && dy < 0) {
    // ball.bounce()
    return;
  }

  bool isAlmostTouchingFloor = windowHeight - (ball.y+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingFloor && dy > 0) {
    // ball.bounce()
    return;
  }

  bool isAlmostTouchingRightWall = windowWidth - (ball.x+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingRightWall && dx > 0) {
    // ball.bounce()
    return;
  }

  bool isAlmostTouchingLeftWall = ball.x-ballMinDistance/2 <= ballMinDistance;
  if (isAlmostTouchingLeftWall && dx < 0) {
    // ball.bounce()
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
  // std::system("clear"); // consome muito tempo
  std::printf("game render DT = %.1lf \n", 1/LastFrameClock::restart().asSeconds());
}


float Game::randomDirectionForBall() {
  float initialDirection = rand() % 2 ? 0 : 180;
  initialDirection = rand() % 360;
  initialDirection = 180;
  return initialDirection;
}

