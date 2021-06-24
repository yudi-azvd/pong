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

  double dt = LastFrameClock::getDeltaTime();
  directionInRadians = direction*degreesToRadians;
  x += stepsPerSecond*cos(directionInRadians)*dt;
  y += stepsPerSecond*sin(directionInRadians)*dt;
}


void Ball::bounce() {
  directionInRadians = direction*degreesToRadians;
  float xComponent = cos(directionInRadians);
  float yComponent = sin(directionInRadians);
  // é possível 

  auto direction = getMainDirection(xComponent, yComponent);

  if (direction.down || direction.up) {
    // ySpeed = -ySpeed
  }
  else if (direction.left || direction.right) {
    // xSpeed = -xSpeed
  }
}


Ball::MainDirection Ball::getMainDirection(float xComponent, float yComponent) {
  MainDirection direction;
  return direction;
}



void Ball::update() {
  circle.setPosition(x, y);
}


void Ball::render(sf::RenderTarget* target) {
  target->draw(circle);
}
