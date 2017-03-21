#ifndef PYLOSPOSITIONSTATE_H
#define PYLOSPOSITIONSTATE_H

#include "pylosfwd.h"
//#include "pylosplayer.h"

namespace ribi {

namespace pylos {

enum class PositionState { player1, player2, empty };
PositionState ToPositionState(const Player& player);
char ToChar(const PositionState state);

bool operator==(const PositionState state, const Player& player);
bool operator!=(const PositionState state, const Player& player);
//bool operator!(const PositionState& state);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSPOSITIONSTATE_H
