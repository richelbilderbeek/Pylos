#pragma GCC diagnostic push



#include <QApplication>
#include "qtpylosmenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::pylos::QtPylosMenuDialog w;
  w.show();
  return a.exec();
}
