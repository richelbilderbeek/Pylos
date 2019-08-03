#ifndef QTPYLOSMENUDIALOG
#define QTPYLOSMENUDIALOG

#pragma GCC diagnostic push

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPylosMenuDialog;
}

namespace ribi {
namespace pylos {

class QtPylosMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtPylosMenuDialog(QWidget *parent = 0);
  QtPylosMenuDialog(const QtPylosMenuDialog&) = delete;
  QtPylosMenuDialog& operator=(const QtPylosMenuDialog&) = delete;
  ~QtPylosMenuDialog() noexcept;

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent * e);

private:
  Ui::QtPylosMenuDialog *ui;
  int m_selected;
  bool m_type_basic;
  bool m_theme_bw;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void OnStart();
  void OnAbout();
  void OnInstructions();
};

} //~namespace pylos
} //~namespace ribi

#endif // QTPYLOSMENUDIALOG
