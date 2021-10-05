#include <iostream>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"


int main() {
  sf::RenderWindow window;
  Game game(&window);

  while (game.isRunning()) {
    game.update();
    game.render();
  }

  return 0;
}