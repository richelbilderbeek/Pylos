#pragma GCC diagnostic push

#include "pyloscurrentmovestate.h"

#include <cassert>
#include <iostream>

#pragma GCC diagnostic pop

ribi::pylos::CurrentMoveState::CurrentMoveState() noexcept
  : m_current_move{},
    m_must_remove(MustRemoveState::no)
{
  assert(IsMoveUnknown());
}

std::string ribi::pylos::CurrentMoveState::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::CurrentMoveState::GetVersionHistory() noexcept
{
  return {
    "2012-05-05: version 2.0: initial release version"
  };
}

bool ribi::pylos::CurrentMoveState::IsMoveMove() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 2;
}

bool ribi::pylos::CurrentMoveState::IsMovePlace() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 1;
}

bool ribi::pylos::CurrentMoveState::IsMoveUnknown() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 0;
}

ribi::pylos::MustRemoveState ribi::pylos::CurrentMoveState::GetMustRemove() const noexcept
{
  return m_must_remove;
}

void ribi::pylos::CurrentMoveState::Restart() noexcept
{
  m_must_remove = MustRemoveState::no;
  m_current_move = Move();
  assert(IsMoveUnknown());
}

void ribi::pylos::CurrentMoveState::SetMove(const Move& move)
{
  assert(m_current_move.m_move.empty());
  assert(m_current_move.m_remove.empty());
  m_current_move = move;
  m_must_remove = MustRemoveState::no;
}

void ribi::pylos::CurrentMoveState::SetMoveTransfer(const Coordinat& from, const Coordinat& to)
{
  assert(IsMoveUnknown());
  assert(m_current_move.m_move.empty());
  m_current_move.m_move.push_back(from);
  m_current_move.m_move.push_back(to);
}

void ribi::pylos::CurrentMoveState::SetMoveSet(const Coordinat& c)
{
  assert(IsMoveUnknown());
  assert(m_current_move.m_move.empty());
  m_current_move.m_move.push_back(c);
}

void ribi::pylos::CurrentMoveState::SetMustRemove(const MustRemoveState must_remove)
{
  assert(!(must_remove == MustRemoveState::player2
    &&   m_must_remove == MustRemoveState::player1)
    && "Cannot set duty to remove from player 1 to player 2");
  assert(!(must_remove == MustRemoveState::player1
    &&   m_must_remove == MustRemoveState::player2)
    && "Cannot set duty to remove from player 2 to player 1");
  m_must_remove = must_remove;
}

void ribi::pylos::CurrentMoveState::SetRemove(const std::vector<Coordinat>& v)
{
  assert(m_must_remove != MustRemoveState::no);
  m_current_move.m_remove = v;
}

bool ribi::pylos::operator==(const CurrentMoveState& lhs, const CurrentMoveState& rhs) noexcept
{
  return lhs.GetMustRemove() == rhs.GetMustRemove()
    && lhs.GetMove() == rhs.GetMove();
}

std::ostream& ribi::pylos::operator<<(std::ostream& os, const CurrentMoveState& s) noexcept
{
  os
    << "move: " << s.GetMove() << '\n'
    << "must_remove: " << s.GetMustRemove()
  ;
  return os;

}
