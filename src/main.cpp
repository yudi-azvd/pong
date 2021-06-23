#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"


int main() {
  sf::RenderWindow window;
  Game game(&window);

  char c;

  sf::Event event;
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Space) {
          game.restartBall();
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      game.movePlayer({"", 1, true});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      game.movePlayer({"", 1, false});
      
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      game.movePlayer({"", 2, true});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      game.movePlayer({"", 2, false});

    game.update();
    game.render();
  }

  return 0;
}