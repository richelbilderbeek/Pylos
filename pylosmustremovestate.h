#ifndef PYLOSMUSTREMOVESTATE_H
#define PYLOSMUSTREMOVESTATE_H

#include <iosfwd>
#include <string>

#include "pylosfwd.h"

namespace ribi {

namespace pylos {

///After placing (Set) or moving (Transfer) a marble, the MustRemoveState
///will be removed. These are:
///- no: no marbles need to be removed before next player's move
///- player1: player1 has to remove one or two marbles. This is determined
///  by the player that places or moves his/her marbles.
///- player2: player2 has to remove one or two marbles. This is determined
///  by the player that places or moves his/her marbles.
enum class MustRemoveState { player1, player2, no };
MustRemoveState ToMustRemoveState(const Player& player);
std::string ToStr(const MustRemoveState state);

//bool operator==(const MustRemoveState& state, const MustRemoveState& player);
//bool operator!=(const MustRemoveState& state, const MustRemoveState& player);
bool operator!(const MustRemoveState& state);

std::ostream& operator<<(std::ostream& os, const MustRemoveState s) noexcept;

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSMUSTREMOVESTATE_H
