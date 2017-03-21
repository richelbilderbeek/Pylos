#include "pylosmenudialog.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylos_menu_dialog_get_info)
{
  MenuDialog d;
  BOOST_CHECK_NO_THROW(d.GetAbout());
  BOOST_CHECK_NO_THROW(d.GetHelp());
  BOOST_CHECK_NO_THROW(d.GetVersion());
  BOOST_CHECK_NO_THROW(d.GetVersionHistory());
}
