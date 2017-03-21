#include "pylosmove.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylos_empty_move_is_invalid)
{
  const Move m;
  BOOST_CHECK(!m.IsValid());
}

BOOST_AUTO_TEST_CASE(pylos_two_empty_moves_are_equal)
{
  const Move m;
  const Move n;
  BOOST_CHECK_EQUAL(m, n);
}

BOOST_AUTO_TEST_CASE(pylos_move)
{
  {
    Move m;
    assert(!m.IsValid());
    Move n;
    assert(m == n);
    m.m_move.push_back(Coordinat(0,0,0));
    n.m_move.push_back(Coordinat(0,0,0));
    BOOST_CHECK_EQUAL(m, n);
  }
  {
    //Valid Moves
    const std::vector<std::string> v
    =
      {
        "(0,0,0)",
        "(0,0,0) !(0,0,0)",
        "(0,0,0) !(0,0,0) !(0,0,0)",
        "(0,0,0)->(0,0,0)",
        "(0,0,0)->(0,0,0) !(0,0,0)",
        "(0,0,0)->(0,0,0) !(0,0,0) !(0,0,0)",
      };
    std::for_each(v.begin(),v.end(),
      [](const std::string& s)
      {
        BOOST_CHECK_NO_THROW(Move m(s));
      }
    );
  }
}
