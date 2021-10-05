#ifndef LASTFRAME_H_INCLUDED
#define LASTFRAME_H_INCLUDED

#include <SFML/System.hpp>


class LastFrameClock {
public:
  static sf::Time restart() {
    time = clock.restart();
    return time;
  }

  static float getDeltaTime() {
    return time.asSeconds();
  }

private:
  static sf::Clock clock;
  static sf::Time time;
};


#endif // LASTFRAME_H_INCLUDED