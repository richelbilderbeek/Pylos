#ifndef PYLOSMOVE_H
#define PYLOSMOVE_H

#include <iosfwd>
#include <string>
#include <vector>

#include "pyloscoordinat.h"

namespace ribi {

namespace pylos {

///PylosMove encapsulates a Pylos move.
///A Pylos move starts with either
/// - placing (Set) a new marble or
/// - moving (Transfer) an existing marble to a higher location
///Both a Set and a Transfer can results in that the player must
///remove either one or two marbles.
struct Move
{
  Move();

  ///Move is constructed from all the members it will hold
  Move(
    const std::vector<Coordinat>& moving,
    const std::vector<Coordinat>& removing);

  ///Move is constructed from Pylos notation
  Move(const std::string& s);

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Test if this Move is valid
  bool IsValid() const noexcept;

  std::string ToStr() const noexcept;

  ///What m_move is, depends on its size:
  ///m_move.size() == 1: placement at m_move[0]
  ///m_move.size() == 2: move from m_move[0] to m_move[1]
  std::vector<Coordinat> m_move;
  std::vector<Coordinat> m_remove;
};

bool operator==(const Move& lhs, const Move& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Move& m) noexcept;

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSMOVE_H
