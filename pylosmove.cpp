#include "pylosmove.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "pyloscoordinat.h"

ribi::pylos::Move::Move()
  : m_move{},
    m_remove{}
{

}

ribi::pylos::Move::Move(
  const std::vector<Coordinat>& moving,
  const std::vector<Coordinat>& removing)
  : m_move{moving},
    m_remove{removing}
{
  assert(!m_move.empty()
    && "In every move a marble must be placed or transferred");
  assert(m_move.size() <= 2);
  assert(m_remove.size() <= 2
    && "At most two marbles are removed in a move");
}

ribi::pylos::Move::Move(const std::string& s)
  : m_move{},
    m_remove{}
{
  //Read first coordinat
  assert(
       s.size() == 7
    || s.size() == 16
    || s.size() == 25
    || s.size() == 34);
  {
    const Coordinat c(s.substr(0,7));
    m_move.push_back(c);
    if (s.size() == 7) return;
  }
  //Test for transfer with/without removal '(Z,X,Y)->(Z,X,Y)'
  if (s[7] == '-' && s[8] == '>')
  {
    const Coordinat c(s.substr(9,7));
    m_move.push_back(c);
    if (s.size() == 16) return;
  }
  //Test for place and single removal '(Z,X,Y) !(Z,X,Y)'
  if (s[7] == ' ' && s[8] == '!')
  {
    const Coordinat c(s.substr(9,7));
    m_remove.push_back(c);
    if (s.size() == 16) return;
  }
  //Test for transfer with single removal '(Z,X,Y)->(Z,X,Y) !(Z,X,Y)'
  assert(s[16] == ' ' && s[17] == '!');
  {
    const Coordinat c(s.substr(18,7));
    m_remove.push_back(c);
    if (s.size() == 25) return;
  }
  //Test for transfer with double removal '(Z,X,Y)->(Z,X,Y) !(Z,X,Y) !(Z,X,Y)'
  assert(s[25] == ' ' && s[26] == '!');
  {
    const Coordinat c(s.substr(27,7));
    m_remove.push_back(c);
  }
  assert(s.size() == 34);
}

std::string ribi::pylos::Move::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::Move::GetVersionHistory() noexcept
{
  return {
    "2012-05-05: version 2.0: initial release version"
  };
}

bool ribi::pylos::Move::IsValid() const noexcept
{
  return
       m_move.size() >= 1
    && m_move.size() <= 2
    && m_remove.size() <= 2;
}

std::string ribi::pylos::Move::ToStr() const noexcept
{
  assert(m_move.size() == 1 || m_move.size() == 2);

  std::string s = m_move[0].ToStr();
  if (m_move.size() == 2)
  {
    s+="->";
    s+=m_move[1].ToStr();
  }
  if (m_remove.empty()) return s;
  assert(m_remove.size() == 1 || m_remove.size() == 2);
  s+=" !";
  s+=m_remove[0].ToStr();
  if (m_remove.size() == 2)
  {
    s+=" !";
    s+=m_remove[0].ToStr();
  }
  return s;
}

bool ribi::pylos::operator==(const Move& lhs, const Move& rhs) noexcept
{
  return lhs.m_move == rhs.m_move
    && lhs.m_remove == rhs.m_remove;
}

std::ostream& ribi::pylos::operator<<(std::ostream& os, const Move& m) noexcept
{
  os << m.ToStr();
  return os;
}
