//---------------------------------------------------------------------------
/*
pylos::Coordinat, Pylos/Phyraos coordinat class
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------



#include "pyloscoordinat.h"

#include <algorithm>
#include <cassert>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>



ribi::pylos::Coordinat::Coordinat(
  const int layer,
  const int x,
  const int y)
  : m_layer(layer),
    m_x(x),
    m_y(y)
{
  assert(IsValid(layer,x,y));
}

ribi::pylos::Coordinat::Coordinat(const std::string& s)
  : m_layer{boost::lexical_cast<int>(s.at(1))},
    m_x{boost::lexical_cast<int>(s.at(3))},
    m_y{boost::lexical_cast<int>(s.at(5))}
{
  assert(s.size() == 7);
  assert(IsValid(m_layer,m_x,m_y));
}

bool ribi::pylos::Coordinat::IsValid(const int layer, const int x, const int y) noexcept
{
  return layer >= 0 && layer < 4
    && x >= 0 && x < 4-layer
    && y >= 0 && y < 4-layer;
}

const std::vector<ribi::pylos::Coordinat> ribi::pylos::GetAllCoordinats() noexcept
{
  std::vector<Coordinat> v;
  for (int z=0; z!=4; ++z)
  {
    for (int y=0; y!=4-z; ++y)
    {
      for (int x=0; x!=4-z; ++x)
      {
        v.push_back(Coordinat(z,x,y));
      }
    }
  }
  assert(v.size() == 30);
  return v;
}

std::string ribi::pylos::Coordinat::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::Coordinat::GetVersionHistory() noexcept
{
  return {
    "2012-05-05: version 2.0: initial release version"
  };
}

bool ribi::pylos::Coordinat::IsValid() const noexcept
{
  return IsValid(m_layer,m_x,m_y);
}

std::string ribi::pylos::Coordinat::ToStr() const noexcept
{
  return "("
    + boost::lexical_cast<std::string>(m_layer)
    + ","
    + boost::lexical_cast<std::string>(m_x)
    + ","
    + boost::lexical_cast<std::string>(m_y)
    + ")";

}

const std::vector<ribi::pylos::Coordinat> ribi::pylos::GetAbove(
  const Coordinat& c)
{
  const int layer = c.GetLayer() + 1;
  const int x = c.GetX();
  const int y = c.GetY();
  //Just get all coordinats
  std::vector<Coordinat> v;
  if (ribi::pylos::Coordinat::IsValid(layer,x-0,y-0)) v.push_back(Coordinat(layer,x-0,y-0));
  if (ribi::pylos::Coordinat::IsValid(layer,x-0,y-1)) v.push_back(Coordinat(layer,x-0,y-1));
  if (ribi::pylos::Coordinat::IsValid(layer,x-1,y-0)) v.push_back(Coordinat(layer,x-1,y-0));
  if (ribi::pylos::Coordinat::IsValid(layer,x-1,y-1)) v.push_back(Coordinat(layer,x-1,y-1));
  return v;
}

const std::vector<ribi::pylos::Coordinat> ribi::pylos::GetBelow(
  const Coordinat& c)
{
  assert(c.IsValid());
  assert(c.GetLayer()!=0);
  const int layer = c.GetLayer() - 1;
  const int x = c.GetX();
  const int y = c.GetY();
  std::vector<Coordinat> v;
  v.push_back(Coordinat(layer,x+0,y+0));
  v.push_back(Coordinat(layer,x+1,y+0));
  v.push_back(Coordinat(layer,x+0,y+1));
  v.push_back(Coordinat(layer,x+1,y+1));
  return v;
}

const std::vector<std::vector<ribi::pylos::Coordinat> > ribi::pylos::GetLines(
  const Coordinat& c)
{
  typedef std::vector<Coordinat> Line;
  std::vector<Line> v;
  const int layer = c.GetLayer();
  if (layer == 2 || layer == 3) return v;
  const int x = c.GetX();
  const int y = c.GetY();
  {
    Line horizontal;
    Line vertical;
    for (int i=0; i!=4-layer; ++i)
    {
      horizontal.push_back(Coordinat(layer,i,y));
      vertical.push_back(Coordinat(layer,x,i));
    }
    assert(boost::numeric_cast<int>(horizontal.size()) == 4-layer);
    assert(boost::numeric_cast<int>(vertical.size()) == 4-layer);
    v.push_back(horizontal);
    v.push_back(vertical);
  }
  assert(v.size() == 2);
  return v;
}

const ribi::pylos::Coordinat ribi::pylos::GetRandomCoordinat() noexcept
{
  const int layer = ( std::rand() >> 4) % 4;
  const int x = ( std::rand() >> 4) % (4 - layer);
  const int y = ( std::rand() >> 4) % (4 - layer);
  assert(ribi::pylos::Coordinat::IsValid(layer,x,y));
  return Coordinat(layer,x,y);
}

const std::vector<std::vector<ribi::pylos::Coordinat> > ribi::pylos::GetSquares(
  const Coordinat& c)
{
  typedef std::vector<Coordinat> Square;
  std::vector<Square> v;
  const int layer = c.GetLayer();
  assert(layer >= 0);
  assert(layer < 4);
  const int x = c.GetX();
  const int y = c.GetY();
  const int sz = 4 - layer;


  if (x > 0 && y > 0)
  {
    Square s;
    s.push_back(Coordinat(layer,x-0,y-0));
    s.push_back(Coordinat(layer,x-0,y-1));
    s.push_back(Coordinat(layer,x-1,y-0));
    s.push_back(Coordinat(layer,x-1,y-1));
    v.push_back(s);
  }
  if (x + 1 < sz && y > 0)
  {
    Square s;
    s.push_back(Coordinat(layer,x+0,y-0));
    s.push_back(Coordinat(layer,x+0,y-1));
    s.push_back(Coordinat(layer,x+1,y-0));
    s.push_back(Coordinat(layer,x+1,y-1));
    v.push_back(s);
  }
  if (x > 0 && y + 1 < sz)
  {
    Square s;
    s.push_back(Coordinat(layer,x-0,y+0));
    s.push_back(Coordinat(layer,x-0,y+1));
    s.push_back(Coordinat(layer,x-1,y+0));
    s.push_back(Coordinat(layer,x-1,y+1));
    v.push_back(s);
  }
  if (x + 1 < sz && y + 1 < sz)
  {
    Square s;
    s.push_back(Coordinat(layer,x+0,y+0));
    s.push_back(Coordinat(layer,x+0,y+1));
    s.push_back(Coordinat(layer,x+1,y+0));
    s.push_back(Coordinat(layer,x+1,y+1));
    v.push_back(s);
  }
  return v;
}

bool ribi::pylos::operator==(const Coordinat& lhs, const Coordinat& rhs) noexcept
{
  return lhs.GetLayer() == rhs.GetLayer()
    && lhs.GetX() == rhs.GetX()
    && lhs.GetY() == rhs.GetY();
}

bool ribi::pylos::operator!=(const Coordinat& lhs, const Coordinat& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::pylos::operator<<(std::ostream& os,const Coordinat& c) noexcept
{
  os << c.ToStr();
  return os;
}
