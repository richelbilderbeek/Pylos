#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QApplication>
#include "pylosboard.h"
#include "pyloscoordinat.h"
#include "pyloscurrentmovestate.h"
#include "pylosgame.h"
#include "pylosmove.h"

#include "qttestpylosmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

///TODO
///- allow a Player to pass turn when he/she has no marble
///- add tooltips to widget
///- add investigation of winners
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  START_TRACE();
  ribi::pylos::QtTestPylosMenuDialog w;
  w.show();
  return a.exec();
}
