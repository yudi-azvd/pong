#include <iostream>
// #include <filesystem>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "renderer.h"


int main() {
  Game game;
  sf::RenderWindow window;
  Renderer renderer(&window, &game);
  sf::SoundBuffer buffer;
  sf::Sound sound;
  // std::string wallHitSoundPath = 
  if (!buffer.loadFromFile("../sounds/wall-hit.wav")) {
    return 0;
  }

  sound.setBuffer(buffer);
  sound.play();

  char c;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      game.start();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      game.movePlayer({1, true});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      game.movePlayer({1, false});
      
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      game.movePlayer({2, true});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      game.movePlayer({2, false});

    game.update();
    renderer.render();
  }

  return 0;
}