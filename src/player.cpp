#include "player.h"


Player::Player() {
  rectangle.setFillColor(sf::Color::White);
  rectangle.setOrigin(width/2, height/2);
  rectangle.setSize({width, height});

  // font.loadFromFile("../ARIALBD.TTF");
}


Player::~Player() {}


void Player::move(float dy) {
  double dt = LastFrameClock::getDeltaTime();
  y += step*dy*dt;
}


void Player::update() {
  // é assim mesmo?
  rectangle.setPosition(x, y);
}


void Player::render(sf::RenderTarget* target) {
  // text.setString("player" + std::to_string(id));
  // text.setFont(font);
  // text.setCharacterSize(12);
  // text.setStyle(sf::Text::Bold);
  // text.setFillColor(sf::Color::Green);
  // text.setPosition(x-width*2, y + height/1.5);
  // target->draw(text);
  target->draw(rectangle);
}