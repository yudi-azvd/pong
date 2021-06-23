#include "ball.h"


Ball::Ball() {
  direction = 0;
  circle.setRadius(radius);
  circle.setFillColor(sf::Color::White);
  circle.setOrigin(radius, radius);
}


Ball::~Ball() {}


void Ball::setDirection(float dir) {
  direction = dir;
}


void Ball::move() {
  if (!canMove)
    return;
  
  directionInRadians = direction*degreesToRadians;
  x += step*cos(directionInRadians);
  y += step*sin(directionInRadians);
}


void Ball::update() {
  circle.setPosition(x, y);
}


void Ball::render(sf::RenderWindow* window) {
  window->draw(circle);
}
