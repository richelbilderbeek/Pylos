#ifndef PYLOSPLAYER_H
#define PYLOSPLAYER_H

#include "pylosfwd.h"
#include "pylospositionstate.h"

namespace ribi {

namespace pylos {

enum class Player { player1, player2 };
///Toggles between the two players
void Toggle(Player& player);
///Convert a PositionState to Player
Player ToPlayer(const PositionState& state);

bool operator==(const Player& player, const PositionState& state);
bool operator!=(const Player& player, const PositionState& state);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSPLAYER_H



