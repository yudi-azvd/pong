#include "player.h"


Player::Player() {
  rectangle.setFillColor(sf::Color::White);
  rectangle.setOrigin(width/2, height/2);
  rectangle.setSize({width, height});
}


Player::~Player() {}


void Player::move(float dy) {
  y += dy;
}



void Player::update() {
  // é assim mesmo?
  rectangle.setPosition(x, y);
}


void Player::render(sf::RenderWindow* w) {
  w->draw(rectangle);
}