//---------------------------------------------------------------------------
/*
TestPylos, tool to test the Pylos classes
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
//From http://www.richelbilderbeek.nl/ToolTestPylos.htm
//---------------------------------------------------------------------------
#ifndef QTTESTPYLOSTESTBOARDDIALOG_H
#define QTTESTPYLOSTESTBOARDDIALOG_H





#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

#include "pylosmove.h"
#include "pylosboard.h"
#include "qtpylosboardwidget.h"


struct QLabel;
struct QTimer;
namespace Ui {
  class QtTestPylosTestBoardDialog;
}

namespace ribi {
namespace pylos {

class QtTestPylosTestBoardDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestPylosTestBoardDialog(QWidget *parent = 0);
  QtTestPylosTestBoardDialog(const QtTestPylosTestBoardDialog&) = delete;
  QtTestPylosTestBoardDialog& operator=(const QtTestPylosTestBoardDialog&) = delete;
  ~QtTestPylosTestBoardDialog() noexcept;

protected:
  

private:
  Ui::QtTestPylosTestBoardDialog *ui;
  boost::shared_ptr<QtPylosBoardWidget> m_widget;
  QTimer * m_timer;

private slots:
  ///OnTimer is called when the auto-play/demo mode clicks randomly
  void OnTimer();

  ///When something changes, the log must be updated
  void UpdateLog();

  void on_button_play_visual_clicked();
  void on_radio_advanced_clicked();
  void on_radio_basic_clicked();
  void on_radio_bw_clicked();
  void on_radio_rb_clicked();
  void on_radio_set_player1_clicked();
  void on_radio_set_player2_clicked();

  void on_slider_tilt_sliderMoved(int position);
};

} //~namespace pylos
} //~namespace ribi

#endif // QTTESTPYLOSTESTBOARDDIALOG_H
