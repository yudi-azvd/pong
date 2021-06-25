#include "game.h"


Game::Game(sf::RenderWindow* w) {
  srand(time(NULL));

  timerForBallToRestart = sf::Clock(); // colocar dentro de initClocks()?

  initSounds();
  initWindow(w);
  initScore();
  initBall();
  initPlayers();
}


Game::~Game() {}


bool Game::isRunning() {
  return !aPlayerReachedMaxScore && !gameEnded;
}


void Game::end() {
  gameEnded = true;
}


void Game::update() {
  if (!isRunning()) {
    window->close();
    return;
  }
  
  if (player1Score == maxScore || player2Score == maxScore) {
    aPlayerReachedMaxScore = true; 
    // TODO:
    // present winner
    // push key to restart
    // push another key to quit game
  }

  if (!ball.canMove && timerForBallToRestart.getElapsedTime().asSeconds() > 1) {
    restartBall();
  }

  moveBall();
  ball.update();
  player1.update();
  player2.update();
}


void Game::restartBall() {
  ball.setDirection(randomDirectionForBall());
  ball.y = (rand() % ((int) windowHeight-40)) + 20; // [20, windowHeight-20)
  ball.x = windowWidth/2;
  ball.canMove = true;
}


void Game::moveBall() {
  if (!ball.canMove)
    return;
  
  if (timerForBallToRestart.getElapsedTime().asSeconds() < 1) {
    return;
  }

  float rad = ball.direction/180*M_PI;
  float dx = cos(rad)*ball.stepsPerSecond;
  float dy = sin(rad)*ball.stepsPerSecond;
  float ballMinDistance = 5;

  bool isAlmostTouchingCeiling = ball.y-ball.radius/2 <= ballMinDistance;
  if (isAlmostTouchingCeiling && dy < 0) {
    sound.setBuffer(wallHitSoundBuffer); sound.play();
    ball.bounce("down");
    return;
  }

  bool isAlmostTouchingFloor = windowHeight - (ball.y+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingFloor && dy > 0) {
    sound.setBuffer(wallHitSoundBuffer); sound.play();
    ball.bounce("up");
    return;
  }

  bool isAlmostTouchingRightWall = windowWidth - (ball.x+ballMinDistance/2) <= ballMinDistance;
  if (isAlmostTouchingRightWall && dx > 0) {
    sound.setBuffer(loseSoundBuffer); sound.play();
    timerForBallToRestart.restart();
    sound.setBuffer(loseSoundBuffer); sound.play();
    ball.canMove = false;
    ++player1Score;
    ball.bounce("left");
    return;
  }

  bool isAlmostTouchingLeftWall = ball.x-ballMinDistance/2 <= ballMinDistance;
  if (isAlmostTouchingLeftWall && dx < 0) {
    sound.setBuffer(loseSoundBuffer); sound.play();
    timerForBallToRestart.restart();
    ball.canMove = false;
    ++player2Score;
    ball.bounce("right");
    return;
  }

  // TODO: a nova direção da boladeve depender de onde ela tocou no jogador.
  if (isBallTouchingPlayer(1)) {
    sound.setBuffer(playerHitSoundBuffer); sound.play();
    ball.bounce("right"); // tanto faz direita ou esquerda
  }

  // TODO: a nova direção da boladeve depender de onde ela tocou no jogador.
  if (isBallTouchingPlayer(2)) {
    sound.setBuffer(playerHitSoundBuffer); sound.play();
    ball.bounce("left"); // tanto faz direita ou esquerda
  }

  ball.move();
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
    return;
  }

  player.move(direction);
}


bool Game::isBallTouchingPlayer(uint8_t playerId) {
  Player& p = playerId == 1 ? player1 : player2;
  float px = p.x;
  float py = p.y;
  float pwidth = p.width;
  float pheight = p.height;
  float x = ball.x;
  float y = ball.y;

  float horizontalCentersDistance = std::abs(px-x);
  float verticalCentersDistance = std::abs(py-y);
  bool areTouchingHorizontally = ball.radius + pwidth/2 >= horizontalCentersDistance; 
  bool areTouchingVertically = ball.radius + pheight/2 >= verticalCentersDistance;
  return areTouchingHorizontally && areTouchingVertically;
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


void Game::initSounds() {
  if (!wallHitSoundBuffer.loadFromFile("../rsc/wall-hit.wav"))
    throw std::runtime_error("could not load file: wall-hit.wav");
  if (!playerHitSoundBuffer.loadFromFile("../rsc/player-hit.wav"))
    throw std::runtime_error("could not load file: player-hit.wav");
  if (!loseSoundBuffer.loadFromFile("../rsc/lose.wav"))
    throw std::runtime_error("could not load file: lose.wav");
}


void Game::initWindow(sf::RenderWindow* w) {
  window = w;
  window->create(
    sf::VideoMode(windowWidth, windowHeight), 
    title, 
    sf::Style::Close | sf::Style::Titlebar);
  window->setFramerateLimit(60);
}


void Game::initScore() {
  resetScore();
  scoreboard = Scoreboard(&player1Score, &player2Score);
}


void Game::initBall() {
  ball.setDirection(randomDirectionForBall());
  restartBall();
}


void Game::initPlayers() {
  player1.id = 1;
  player1.x = sideOffset;
  player1.y = windowHeight/2;

  player2.id = 2;
  player2.x = windowWidth - sideOffset;
  player2.y = windowHeight/2;
}
