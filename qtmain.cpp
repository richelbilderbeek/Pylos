



#include <QApplication>
#include "qtpylosmenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::pylos::QtPylosMenuDialog w;
  w.show();
  return a.exec();
}
