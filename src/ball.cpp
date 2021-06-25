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


/**
 * Esse método de determinar só funciona se a bola sabe que o player é um retângulo :(
 */
bool Ball::isTouchingPlayer(float px, float py, float pwidth, float pheight) {
  float horizontalCentersDistance = std::abs(px-x);
  float verticalCentersDistance = std::abs(py-y);
  bool areTouchingHorizontally = radius + pwidth/2 >= horizontalCentersDistance; 
  bool areTouchingVertically = radius + pheight/2 >= verticalCentersDistance;
  return areTouchingHorizontally && areTouchingVertically;
}


void Ball::update() {
  circle.setPosition(x, y);
}


void Ball::render(sf::RenderTarget* target) {
  target->draw(circle);
}
