#include <iostream>
// #include <filesystem>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "renderer.h"


int main() {
  Game game;
  sf::RenderWindow window(sf::VideoMode(game.windowWidth, game.windowHeight), "Pong");
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
      
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        game.movePlayer({1, true});
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        game.movePlayer({1, false});
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        game.movePlayer({2, true});
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        game.movePlayer({2, false});
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        game.start();
    }

    game.moveBall();
    renderer.render();
  }

  return 0;
}