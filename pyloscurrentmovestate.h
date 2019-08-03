#ifndef PYLOSCURRENTMOVESTATE_H
#define PYLOSCURRENTMOVESTATE_H

#include <vector>





#include <boost/checked_delete.hpp>

#include "pyloscoordinat.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"


namespace ribi {

namespace pylos {

///CurrentMoveState contains the state of the current Move.
///CurrentMoveState is used by pylos::Game, to incrementally keep track of the
///ongoing move
struct CurrentMoveState
{
  CurrentMoveState() noexcept;

  ///Obtain the current Move in process
  const Move& GetMove() const noexcept { return m_current_move; }

  ///Obtain if the first part of the move has taken place and
  ///if the current player must remove one or two marbles
  MustRemoveState GetMustRemove() const noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;


  ///Is it unknown what kind of Move this is?
  bool IsMoveUnknown() const;
  bool IsMoveMove() const;
  bool IsMovePlace() const;

  void Restart() noexcept;

  ///Set a complete Move directly
  void SetMove(const Move& move);

  ///Set the transfer part of a move,enabling
  void SetMoveTransfer(const Coordinat& from, const Coordinat& to);

  void SetMoveSet(const Coordinat& c);

  ///Set the duty of one or none of the players
  void SetMustRemove(const MustRemoveState must_remove);
  void SetRemove(const std::vector<Coordinat>& v);

  private:
  Move m_current_move;
  MustRemoveState m_must_remove;
};

bool operator==(const CurrentMoveState& lhs, const CurrentMoveState& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const CurrentMoveState& s) noexcept;

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSCURRENTMOVESTATE_H
