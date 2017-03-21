#include "pyloscurrentmovestate.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylose_movestate)
{
  const Coordinat c(0,1,1);
  CurrentMoveState s;
  BOOST_CHECK(s.IsMoveUnknown());
  BOOST_CHECK(!s.GetMustRemove());
  s.SetMoveSet(c);
  BOOST_CHECK(!s.IsMoveUnknown());
  const Move m = s.GetMove();
  BOOST_CHECK_EQUAL(m.m_move.size(), 1);
  BOOST_CHECK_EQUAL(m.m_move[0], c);
  BOOST_CHECK(m.m_remove.empty());
  s.Restart();
  CurrentMoveState t;
  BOOST_CHECK_EQUAL(s, t);
}
