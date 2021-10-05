#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED


#include <iostream>
#include <cstdint>


struct GameCommand {
  std::string type; // talvez type seja desnecessário.
};


struct MovePlayerCommand : public GameCommand {
  uint8_t playerId;
  bool upDirection;
};





#endif // COMMANDS_H_INCLUDED