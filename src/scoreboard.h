#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>


class Scoreboard {
public:  
  Scoreboard();
  
  ~Scoreboard();

  Scoreboard(uint8_t* p1Score, uint8_t* p2Score);

  std::string getScore() {
    return "score: " + std::to_string(*player1Points) + " x " + std::to_string(*player2Points);
  }

  void reset() {
    *player1Points = 0;
    *player2Points = 0;
  }

  void setPosition(float x, float y);

  void setSize(float w, float h) {
    width = w;
    height = h;
  }

  void update();

  void render(sf::RenderWindow* target);

private:
  float x, y;
  float width, height;
  uint8_t* player1Points = 0;
  uint8_t* player2Points = 0;
  bool visible = false;

  sf::Text* text;
  sf::Font font;
  sf::RectangleShape rect;

  const std::string seprationBetweenPlayerPoints = "\t\t\t";

  void initFonts();
  void initText();
};


#endif // SCOREBOARD_H_INCLUDED