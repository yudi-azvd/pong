#ifndef MOVEPLAYERCOMMAND_H_INCLUDED
#define MOVEPLAYERCOMMAND_H_INCLUDED

#include <cstdint>


struct MovePlayerCommand {
  uint8_t playerId;
  bool upDirection;
};


#endif // MOVEPLAYERCOMMAND_H_INCLUDED