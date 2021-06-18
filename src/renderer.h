#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "game.h"


class Renderer {
public:
  sf::RenderWindow* window;

  Game* game;

  Renderer(sf::RenderWindow* window, Game* game);
  
  ~Renderer();

  void render();

private:
  sf::RectangleShape rectangle;

  sf::CircleShape circle;

  void renderPlayer(Player& player);

  void renderBall(Ball& ball);
};


#endif // RENDERER_H_INCLUDED