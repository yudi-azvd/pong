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

  // acho que não funciona por que o passo do player é muito grande
  float playerMinDistance = 10.0;

  bool isAlmostTouchingCeiling = player.y-player.height/2 <= playerMinDistance;
  if (isAlmostTouchingCeiling && command.upDirection) {
    return;
  }

  bool isAlmostTouchingFloor = windowHeight - (player.y+player.height/2) <= playerMinDistance;
  if (isAlmostTouchingFloor && !command.upDirection) {
    // std::printf("player%d top %.2f\n", player.id, player.y+player.height/2);
    // std::printf("player%d distance: %.2f\n", player.id, windowHeight - (player.y+player.height/2));
    return;
  }

  player.move(direction*playerStep);
}


void Game::moveBall() {
  if (!ball.canMove)
    return;

  float rad = ball.direction/180*M_PI;
  float dx = cos(rad)*ball.stepsPerSecond;
  float dy = sin(rad)*ball.stepsPerSecond;
  float ballMinDistance = 5;

  bool isAlmostTouchingCeiling = ball.y-ball.radius/2 <= ballMinDistance;
  if (isAlmostTouchingCeiling && dy < 0) {
    ball.bounce("down");
    return;
  }

  bool isAlmostTouchingFloor = windowHeight - (ball.y+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingFloor && dy > 0) {
    ball.bounce("up");
    return;
  }

  bool isAlmostTouchingRightWall = windowWidth - (ball.x+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingRightWall && dx > 0) {
    // player 1 ganha ponto
    ball.bounce("left");
    return;
  }

  bool isAlmostTouchingLeftWall = ball.x-ballMinDistance/2 <= ballMinDistance;
  if (isAlmostTouchingLeftWall && dx < 0) {
    ball.bounce("right");
    // player 2 ganha ponto
    return;
  }

  // No futuro, a nova direção da bola depende de onde ela tocou no jogador.
  if (ball.isTouchingPlayer(player1.x, player1.y, player1.width, player1.height)) {
    ball.bounce("right"); // ball.bounce("vertical")?
  }

  if (ball.isTouchingPlayer(player2.x, player2.y, player2.width, player2.height)) {
    ball.bounce("left"); // tanto faz direita ou esquerda
  }

  ball.move();
}


void Game::moveBallWithMouse(float x, float y) {
  if (ball.isTouchingPlayer(player1.x, player1.y, player1.width, player1.height)) {
    ball.bounce("right"); // ball.bounce("vertical")?
    return;
  }

  if (ball.isTouchingPlayer(player2.x, player2.y, player2.width, player2.height)) {
    std::printf(" bunce player 2 \n");
    ball.bounce("left"); // ball.bounce("vertical")?
    return;
  }

  ball.x = x;
  ball.y = y;
}


void Game::render() {
  window->clear();
  player1.render(window);
  player2.render(window);
  ball.render(window);
  window->display();
  LastFrameClock::restart();
}


float Game::randomDirectionForBall() {
  float toTheLeftOrToTheRightOffset = rand() % 2 ? 0. : 180.;
  int amplitude = 35;
  float randomDirection = (rand() % (2*amplitude)) - amplitude; // [-amp, amp)
  return randomDirection + toTheLeftOrToTheRightOffset;
}

