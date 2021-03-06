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


#include "qtpyloswondialog.h"

#include <cassert>

#include "ui_qtpyloswondialog.h"
#include "pyloswinner.h"


ribi::QtPylosWonDialog::QtPylosWonDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtPylosWonDialog)
{
  ui->setupUi(this);
}

ribi::QtPylosWonDialog::~QtPylosWonDialog() noexcept
{
  delete ui;
}

void ribi::QtPylosWonDialog::SetWinner(const pylos::Winner winner)
{
  if (winner == pylos::Winner::player1)
    ui->label_sprite->setPixmap(QPixmap(":/images/sprite_player1.png"));
  else
    ui->label_sprite->setPixmap(QPixmap(":/images/sprite_player2.png"));
}
