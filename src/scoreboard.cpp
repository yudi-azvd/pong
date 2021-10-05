#include "scoreboard.h"

Scoreboard::Scoreboard() {}


Scoreboard::Scoreboard(uint8_t* p1Score, uint8_t* p2Score) {
  initFonts();
  initText();
  player1Points = p1Score;
  player2Points = p2Score;
}


Scoreboard::~Scoreboard() {
  delete text;
}


void Scoreboard::update() {
  std::string placeholder = std::to_string(*player1Points)
   + seprationBetweenPlayerPoints + std::to_string(*player2Points);
  text->setString(placeholder);
  text->setPosition(x, y);
}


void Scoreboard::render(sf::RenderWindow* target) {
  target->draw(*text);
}


void Scoreboard::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}


void Scoreboard::initFonts() {
  if (!font.loadFromFile("../rsc/bit5x5.ttf"))
    throw std::runtime_error("could not load file: bit5x5.ttf");
}


void Scoreboard::initText() {
  text = new sf::Text("SCOREBOARD", font);
  text->setCharacterSize(52);
  text->setFillColor(sf::Color::White);
  text->setStyle(sf::Text::Regular);
  text->setPosition(x, y);
  text->setOrigin({
    text->getLocalBounds().width/4, // deveria ser /2 pra centralizar, mas /4 que funciona
    text->getLocalBounds().height/4,
  });
}
