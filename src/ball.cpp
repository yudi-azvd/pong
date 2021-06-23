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
  // float lastDisp = sqrt(x*x + x*x);
  x += step*cos(directionInRadians)*dt;
  y += step*sin(directionInRadians)*dt;
  // float newDisp = sqrt(x*x + x*x);
  // std::printf("ball last ");
}


void Ball::update() {
  circle.setPosition(x, y);
}


void Ball::render(sf::RenderTarget* target) {
  target->draw(circle);
}
