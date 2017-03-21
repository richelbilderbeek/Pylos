#include "pylosmustremovestate.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "pylosplayer.h"

ribi::pylos::MustRemoveState ribi::pylos::ToMustRemoveState(const Player& player)
{
  switch (player)
  {
    case Player::player1: return MustRemoveState::player1;
    case Player::player2: return MustRemoveState::player2;
  }
  assert(!"Unknown value for Player");
  throw std::logic_error("Unknown value for Player");
}

std::string ribi::pylos::ToStr(const MustRemoveState state)
{
  switch (state)
  {
    case MustRemoveState::player1: return "player1";
    case MustRemoveState::player2: return "player2";
    case MustRemoveState::no: return "no";
  }
  assert(!"Unknown value for MustRemoveState");
  throw std::logic_error("Unknown value for MustRemoveState");
}

bool ribi::pylos::operator!(const MustRemoveState& state)
{
  return state == MustRemoveState::no;
}

std::ostream& ribi::pylos::operator<<(std::ostream& os, const MustRemoveState s) noexcept
{
  os << ToStr(s);
  return os;
}
