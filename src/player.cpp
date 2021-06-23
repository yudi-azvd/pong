#include "player.h"


Player::Player() {
  rectangle.setFillColor(sf::Color::White);
  rectangle.setOrigin(width/2, height/2);
  rectangle.setSize({width, height});
}


Player::~Player() {}


void Player::render(sf::RenderWindow* w) {
  // set positoin deveria estar em update()
  rectangle.setPosition(x, y);
  w->draw(rectangle);
}