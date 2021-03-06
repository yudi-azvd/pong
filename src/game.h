#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "ballonplayercollision.h"
#include "player.h"
#include "ball.h"
#include "scoreboard.h"
#include "command.h"
#include "lastframeclock.h"
#include "states.h"


class Game {
public:
  Game(sf::RenderWindow* window);

  ~Game();

  bool isRunning();
  
  void end();

  void update();

  void restart();

  void restartBall();
  
  void movePlayer(MovePlayerCommand command);
  
  void moveBall();
  
  void moveBallWithMouse(float x, float y);
  
  void render();

private:
  void handleEvent();

  void showWinner();

  std::string title = "Pong";
  State state = State::BALL_WAIT;
  sf::RenderWindow* window;
  const float windowHeight = 560;
  const float windowWidth = 720;
  bool gameEnded = false;
  bool playerWantsToQuit = false;

  Ball ball;
  int wait = 1;
  bool debugBallMode = false;
  Player player1;
  Player player2;
  bool playersCanMove = false;
  bool aPlayerReachedMaxScore = false;
  
  uint8_t player1Score = 0;
  uint8_t player2Score = 0;
  const uint8_t maxScore = 5;

  sf::SoundBuffer wallHitSoundBuffer;
  sf::SoundBuffer playerHitSoundBuffer;
  sf::SoundBuffer loseSoundBuffer;
  sf::Sound sound;

  sf::Font font;
  sf::Text winnerText;
  sf::Text whatToDoNextText;

  sf::Clock timerForBallToMove;

  /**
   * Estados/cenas:
   *    tela inicial: bola batendo nas paredes,
   *      jogadores invisíveis, ou menu
   *    jogo normal
   *    bola parada - 2s
   *    mostrando ganhador 
   *      - apertar SPACE pra reiniciar
   *      - apertar ESC pra sair
   */

  Scoreboard* scoreboard;

  const float sideOffset = 40;

  float randomDirectionForBall();

  bool isBallTouchingPlayer(uint8_t playerId, BallOnPlayerCollision&);

  void resetScore() {
    player1Score = 0;
    player2Score = 0;
  }

  void initWindow(sf::RenderWindow* w);
  void initScoreboard();
  void initBall();
  void initPlayers();
  void initSounds();
  void initFont();
  void initTexts();
  void updateText();
};


#endif // GAME_H_INCLUDED