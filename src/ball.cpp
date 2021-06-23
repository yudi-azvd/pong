#include "ball.h"


Ball::Ball() {
  circle.setRadius(radius);
  circle.setFillColor(sf::Color::White);
  // circl
}


Ball::~Ball() {}


void Ball::move() {
  if (!canMove)
    return;
}


void Ball::render(sf::RenderWindow* window) {
  // set positoin deveria estar em update()
  circle.setPosition(x, y);
  window->draw(circle);
}
