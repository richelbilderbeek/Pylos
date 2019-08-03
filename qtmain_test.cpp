



#include <QApplication>
#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"

#include "qttestpylosmenudialog.h"


///TODO
///- allow a Player to pass turn when he/she has no marble
///- add tooltips to widget
///- add investigation of winners
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::pylos::QtTestPylosMenuDialog w;
  w.show();
  return a.exec();
}
