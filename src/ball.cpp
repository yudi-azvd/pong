#include "ball.h"


Ball::Ball() {
  direction = 0;
  shape.setSize({size, size});
  shape.setFillColor(sf::Color::White);
  shape.setOrigin(size/2, size/2);
  center.setFillColor(sf::Color::Red);
  center.setSize({2, 2});
  center.setOrigin(2, 2);
}


Ball::~Ball() {}


void Ball::setDirection(float dir) {
  direction = dir;
}


void Ball::move() {
  double dt = LastFrameClock::getDeltaTime();
  directionInRadians = direction*degreesToRadians;
  x += stepsPerSecond*cos(directionInRadians)*dt;
  y += stepsPerSecond*sin(directionInRadians)*dt;
}


void Ball::bounce(std::string newDirection) {
  directionInRadians = direction*degreesToRadians;
  float xMagnitude = cos(directionInRadians);
  float yMagnitude = sin(directionInRadians);

  if (newDirection == "up" || newDirection == "down") // vertical
    yMagnitude = -yMagnitude;
  else { // horizontal
    xMagnitude = -xMagnitude;
  }

  this->direction = atan2(yMagnitude, xMagnitude)*radiansToDegrees;
}


void Ball::update() {
  shape.setPosition(x, y);
  // center.setPosition(x, y);
}


void Ball::render(sf::RenderTarget* target) {
  target->draw(shape);
  // target->draw(center);
}
