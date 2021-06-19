#include "renderer.h"


Renderer::Renderer(sf::RenderWindow* w, Game* g) {
  window = w;
  game = g;

  window->create(sf::VideoMode(
    g->windowWidth, g->windowHeight), g->title);

  circle.setRadius(g->ball.radius);
  circle.setOrigin(g->ball.radius, g->ball.radius);
  circle.setFillColor(sf::Color::White);
  
  rectangle.setFillColor(sf::Color::White);
  rectangle.setOrigin(g->player1.width/2, g->player1.height/2);
  rectangle.setSize({g->player1.width, g->player1.height});
}


Renderer::~Renderer() {}


void Renderer::render() {
  window->clear();
  renderPlayer(game->player1);
  renderPlayer(game->player2);
  renderBall(game->ball);
  window->display();
}


void Renderer::renderPlayer(Player& player) {
  rectangle.setPosition(player.x, player.y);
  window->draw(rectangle);
}


void Renderer::renderBall(Ball& ball) {
  circle.setPosition(ball.x, ball.y);
  window->draw(circle);
}
