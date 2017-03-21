#include "pyloscoordinat.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylos_coordinat)
{
  //if (verbose) { TRACE("Test PylosCoordinat operators"); }
  {
    const Coordinat c1(0,2,2);
    const Coordinat c2(0,2,3);
    const Coordinat c3(0,3,2);
    const Coordinat c1_too(0,2,2);
    BOOST_CHECK_NE(c1, c2);
    BOOST_CHECK_NE(c1, c3);
    BOOST_CHECK_EQUAL(c1, c1_too);
    BOOST_CHECK_NE(c2, c3);
  }
  //if (verbose) { TRACE("Test Coordinat GetBelow function on (1,0,1)"); }
  {
    const std::vector<Coordinat> v
      = GetBelow(Coordinat(1,0,1));
    BOOST_CHECK_EQUAL(v.size(), 4);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,0,1))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,0,2))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,1,1))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,1,2))
      != v.end());
  }
  //if (verbose) { TRACE("Test Coordinat GetBelow function on (1,0,2)"); }
  {
    const std::vector<Coordinat> v
      = GetBelow(Coordinat(1,0,2));
    BOOST_CHECK(v.size() == 4);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,0,2))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,0,3))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,1,2))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(0,1,3))
      != v.end());
  }
  //if (verbose) { TRACE("Test Coordinat GetAbove function on (0,0,0)"); }
  {
    const std::vector<Coordinat> v
      = GetAbove(Coordinat(0,0,0));
    BOOST_CHECK(v.size() == 1);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(1,0,0))
      != v.end());
  }
  //if (verbose) { TRACE("Test Coordinat GetAbove function on (0,1,2)"); }
  {
    const std::vector<Coordinat> v
      = GetAbove(Coordinat(0,1,2));
    BOOST_CHECK(v.size() == 4);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(1,0,1))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(1,0,2))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(1,1,1))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(1,1,2))
      != v.end());
  }
  //if (verbose) { TRACE("Test Coordinat GetAbove function on (1,2,1)"); }
  {
    const std::vector<Coordinat> v
      = GetAbove(Coordinat(1,2,1));
    BOOST_CHECK(v.size() == 2);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(2,1,0))
      != v.end());
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(2,1,1))
      != v.end());
  }
  //if (verbose) { TRACE("Test Coordinat GetAbove function on (2,0,0)"); }
  {
    const std::vector<Coordinat> v
      = GetAbove(Coordinat(2,0,0));
    BOOST_CHECK(v.size() == 1);
    BOOST_CHECK(std::find(v.begin(),v.end(),Coordinat(3,0,0))
      != v.end());
  }
}

