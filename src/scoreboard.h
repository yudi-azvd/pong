#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include <stdint.h>
#include <SFML/Graphics.hpp>


class Scoreboard {
public:
  float x, y;
  float width, height;
  uint8_t* player1Points = 0;
  uint8_t* player2Points = 0;
  bool visible = false;
  
  Scoreboard() { }

  Scoreboard(uint8_t* p1Score, uint8_t* p2Score) {
    player1Points = p1Score;
    player2Points = p2Score;
  }

  std::string getScore() {
    return "score: " + std::to_string(*player1Points) + " x " + std::to_string(*player2Points);
  }

  void setVisible(bool visible=true) {
    this->visible = visible;
  }

  void setPostion(float x, float y) {
    this->x = x;
    this->y = y;
  }

  void setSize(float w, float h) {
    width = w;
    height = h;
  }

private:
  // void render() {
  //   std::printf("%d x %d\n", player1Points, player2Points);
  // }
};


#endif // SCOREBOARD_H_INCLUDED