//---------------------------------------------------------------------------
/*
Pylos, Pylos/Pyraos game
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
//From http://www.richelbilderbeek.nl/GamePylos.htm
//---------------------------------------------------------------------------
#include "pylosmenudialog.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "canvas.h"
#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"
#include "pylosplayer.h"

#include "textcanvas.h"


ribi::pylos::MenuDialog::MenuDialog() noexcept
{

}


int ribi::pylos::MenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc != 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  const boost::shared_ptr<Game> game {
    Game::CreateBasicGame()
  };

  std::cout
    << (*game->GetBoard()->ToTextCanvas()) << std::endl
    << std::endl;
  return 0;
}

ribi::About ribi::pylos::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "Pylos",
    "Pylos/Pyraos game",
    "the 30th of January 2014",
    "2010-2015",
    "http://www.richelbilderbeek.nl/GamePylos.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("pylos::Board version: " + pylos::Board::GetVersion());
  a.AddLibrary("pylos::Coordinat version: " + pylos::Coordinat::GetVersion());
  a.AddLibrary("pylos::CurrentMoveState version: " + pylos::CurrentMoveState::GetVersion());
  a.AddLibrary("pylos::Game version: " + pylos::Game::GetVersion());
  a.AddLibrary("pylos::Move version: " + pylos::Move::GetVersion());
  a.AddLibrary("Canvas version: " + Canvas::GetVersion());
  a.AddLibrary("TextCanvas version: " + TextCanvas::GetVersion());
  return a;
}

ribi::Help ribi::pylos::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::pylos::MenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::pylos::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-09-22: version 1.0: initial release version",
    "2012-05-28: version 2.0: improved version to work with ProjectRichelBilderbeek",
    "2014-01-30: version 2.1: improved self-tests"
  };
}

