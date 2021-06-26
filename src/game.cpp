#include "game.h"


Game::Game(sf::RenderWindow* w) {
  srand(time(NULL));

  timerForBallToRestart = sf::Clock(); // colocar dentro de initClocks()?

  initFont();
  initTexts();
  initSounds();
  initWindow(w);
  initScoreboard();
  initBall();
  initPlayers();
}


Game::~Game() {}


bool Game::isRunning() {
  // return !aPlayerReachedMaxScore && !gameEnded;
  return !playerWantsToQuit;
}



void Game::handleEvent() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      playerWantsToQuit = true;
      window->close();
    }
    if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::Space) {
        this->restart();
      }
    }
  }



  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    playerWantsToQuit = true;
    window->close();
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    this->movePlayer({"", 1, true});
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    this->movePlayer({"", 1, false});
    
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    this->movePlayer({"", 2, true});
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    this->movePlayer({"", 2, false});
}


void Game::update() {
  this->handleEvent();

  updateText();

  moveBall();
  scoreboard->update();
  ball.update();
  player1.update();
  player2.update();

  aPlayerReachedMaxScore = player1Score == maxScore || player2Score == maxScore;
  if (aPlayerReachedMaxScore) {
    showWinner();
    return;
  }

  if (!ball.canMove && timerForBallToRestart.getElapsedTime().asSeconds() > 1) {
    restartBall();
  }
}


void Game::restart() {
  if (!aPlayerReachedMaxScore) {
    return;
  }
  restartBall();
  initPlayers();
  winnerText.setString("");
  whatToDoNextText.setString("");
  scoreboard->reset();
}


void Game::showWinner() {
  uint8_t winnerId = player1Score > player2Score ? 1 : 2; 
  std::string winner = "PLAYER " + std::to_string(winnerId) + "\n\tWINS";
  winnerText.setString(winner);
  whatToDoNextText.setString(
    "press <SPACE> to restart game\n"
    "press <ESC>    to quit game");
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
    ball.canMove = false;
    ball.bounce("left");
    ++player1Score;
    return;
  }

  bool isAlmostTouchingLeftWall = ball.x-ballMinDistance/2 <= ballMinDistance;
  if (isAlmostTouchingLeftWall && dx < 0) {
    sound.setBuffer(loseSoundBuffer); sound.play();
    timerForBallToRestart.restart();
    ball.canMove = false;
    ball.bounce("right");
    ++player2Score;
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
  scoreboard->render(window);
  player1.render(window);
  player2.render(window);
  ball.render(window);
  window->draw(winnerText);
  window->draw(whatToDoNextText);
  window->display();
  LastFrameClock::restart();
}


float Game::randomDirectionForBall() {
  float toTheLeftOrToTheRightOffset = rand() % 2 ? 0. : 180.;
  int amplitude = 35;
  float randomDirection = (rand() % (2*amplitude)) - amplitude; // [-amp, amp)
  return randomDirection + toTheLeftOrToTheRightOffset;
}


void Game::initWindow(sf::RenderWindow* w) {
  window = w;
  window->create(
    sf::VideoMode(windowWidth, windowHeight), 
    title, 
    sf::Style::Close | sf::Style::Titlebar);
  window->setFramerateLimit(60);
}


void Game::initScoreboard() {
  scoreboard = new Scoreboard(&player1Score, &player2Score);
  scoreboard->setPosition(windowWidth/2, 80);  
  resetScore();
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


void Game::initSounds() {
  if (!wallHitSoundBuffer.loadFromFile("../rsc/wall-hit.wav"))
    throw std::runtime_error("could not load file: wall-hit.wav");
  if (!playerHitSoundBuffer.loadFromFile("../rsc/player-hit.wav"))
    throw std::runtime_error("could not load file: player-hit.wav");
  if (!loseSoundBuffer.loadFromFile("../rsc/lose.wav"))
    throw std::runtime_error("could not load file: lose.wav");
}


void Game::initFont() {
  if (!font.loadFromFile("../rsc/bit5x5.ttf"))
    throw std::runtime_error("game::initFont could not load font");
}


void Game::initTexts() {
  winnerText = sf::Text("", font);
  winnerText.setCharacterSize(64);
  winnerText.setFillColor(sf::Color::White);
  winnerText.setPosition(windowWidth/2, windowHeight/2);

  whatToDoNextText = sf::Text("", font);
  whatToDoNextText.setCharacterSize(16);
  whatToDoNextText.setFillColor(sf::Color::White);
  whatToDoNextText.setPosition(
    // windowWidth/2, 
    winnerText.getPosition().x,
    windowHeight/2+64+2*16+8
  );
}


void Game::updateText() {
  winnerText.setOrigin(
    winnerText.getLocalBounds().width/2,
    winnerText.getLocalBounds().height/2
  );
  whatToDoNextText.setOrigin(
    whatToDoNextText.getLocalBounds().width/2,
    whatToDoNextText.getLocalBounds().height/2
  );
}