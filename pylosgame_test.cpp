#include "pylosgame.h"

#include <boost/test/unit_test.hpp>

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylos_game)
{
  const int testing_depth = 1;

  //if (verbose) { TRACE("Test ribi::pylos::Game::operator== for different game types"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    BOOST_CHECK(*a != *b);
    a->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a != *b);
    b->Do("(0,0,0)");
    BOOST_CHECK(*a != *b);
  }
  //if (verbose) { TRACE("Test ribi::pylos::Game::operator== for same game types"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateAdvancedGame();
    BOOST_CHECK(*a == *b);
    a->Do("(0,0,0)");
    BOOST_CHECK(*a != *b);
    b->Do("(0,0,0)");
    BOOST_CHECK(*a == *b);
  }
  //if (verbose) { TRACE("Test basic Game dynamics using Set and Remove"); }
  {
    // 1
    // 1
    // 1 22
    // 1 22
    // Only advanced game must detect player 1's line
    // Both games must detect player 2's square
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,0)"));
    b->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,3,0)"));
    b->Set(Coordinat("(0,3,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,1)"));
    b->Set(Coordinat("(0,0,1)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,2,0)"));
    b->Set(Coordinat("(0,2,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    a->Set(Coordinat("(0,0,2)"));
    b->Set(Coordinat("(0,0,2)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Set(Coordinat("(0,2,1)"));
    b->Set(Coordinat("(0,2,1)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    //BoardAdvanced responds to the creation of a line
    a->Set(Coordinat("(0,0,3)")); //Line
    b->Set(Coordinat("(0,0,3)")); //Line
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1); //No toggle
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2); //Toggle
    BOOST_CHECK( a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK( a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,0,0)"))));
    BOOST_CHECK(!b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,0,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,0,0)")));
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2); //Toggle
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);

    //BoardAdvanced and BoardBasic respond to the creation of a square
    a->Set(Coordinat("(0,3,1)")); //Square
    b->Set(Coordinat("(0,3,1)")); //Square
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2); //No toggle
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2); //No toggle
    BOOST_CHECK(a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    BOOST_CHECK(b->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    BOOST_CHECK(a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    BOOST_CHECK(b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    b->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
  }
  //if (verbose) { TRACE("Test ribi::pylos::Game::Clone of GameBasic"); }
  {
    boost::shared_ptr<Game> a = CreateBasicGame();
    boost::shared_ptr<Game> b(new Game(*a));
    boost::shared_ptr<Game> c = CreateAdvancedGame();
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
    a->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(*a != *c);
    b->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
    c->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a != *c);
    BOOST_CHECK(*b != *c);
  }
  //if (verbose) { TRACE("Test ribi::pylos::Game::Clone of GameAdvanced"); }
  {
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b(new Game(*a));
    boost::shared_ptr<Game> c = CreateBasicGame();
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
    a->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(*a != *c);
    b->Set(Coordinat("(0,0,0)"));
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
  }
  //if (verbose) { TRACE("Test Clone of played GameBasic"); }
  {
    boost::shared_ptr<Game> a = CreateBasicGame();
    a->Set(Coordinat("(0,0,0)"));
    const boost::shared_ptr<Game> b(new Game(*a));
    BOOST_CHECK(*a == *b);
    b->Set(Coordinat("(0,1,0)"));
    BOOST_CHECK(*a != *b);
  }
  //if (verbose) { TRACE("Test Clone of played BoardAdvanced"); }
  {
    const boost::shared_ptr<Game> a = CreateAdvancedGame();
    a->Set(Coordinat("(0,0,0)"));
    const boost::shared_ptr<Game> b(new Game(*a));
    BOOST_CHECK(*a == *b);
    b->Set(Coordinat("(0,1,0)"));
    BOOST_CHECK(*a != *b);
  }
  //if (verbose) { TRACE("Test basic Game dynamics using full moves"); }
  {
    // 1
    // 1
    // 1 22
    // 1 22
    // Only advanced game must detect player 1's line
    // Both games must detect player 2's square
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,0,0)"));
    b->Do(Move("(0,0,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,3,0)"));
    b->Do(Move("(0,3,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    a->Do(Move("(0,0,1)"));
    b->Do(Move("(0,0,1)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,2,0)"));
    b->Do(Move("(0,2,0)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    a->Do(Move("(0,0,2)"));
    b->Do(Move("(0,0,2)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    a->Do(Move("(0,2,1)"));
    b->Do(Move("(0,2,1)"));
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());

    //BoardAdvanced responds to the creation of a line
    BOOST_CHECK(!a->CanDo("(0,0,3)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,0)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,1)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,2)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,3)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,0) !(0,0,1)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,0) !(0,0,2)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,0) !(0,0,3)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,1) !(0,0,0)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,1) !(0,0,2)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,1) !(0,0,3)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,2) !(0,0,0)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,2) !(0,0,1)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,2) !(0,0,3)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,3) !(0,0,0)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,3) !(0,0,1)"));
    BOOST_CHECK(a->CanDo("(0,0,3) !(0,0,3) !(0,0,2)"));
    BOOST_CHECK(!a->CanDo("(0,0,3) !(0,0,0) !(0,0,0)"));
    BOOST_CHECK(!a->CanDo("(0,0,3) !(0,0,1) !(0,0,1)"));
    BOOST_CHECK(!a->CanDo("(0,0,3) !(0,0,2) !(0,0,2)"));
    BOOST_CHECK(!a->CanDo("(0,0,3) !(0,0,3) !(0,0,3)"));
    BOOST_CHECK(b->CanDo("(0,0,3)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,0)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,1)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,2)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,3)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,1)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,2)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,3)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,0)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,2)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,3)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,0)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,1)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,3)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,0)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,1)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,2)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,0) !(0,0,0)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,1) !(0,0,1)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,2) !(0,0,2)"));
    BOOST_CHECK(!b->CanDo("(0,0,3) !(0,0,3) !(0,0,3)"));
    a->Do(Move("(0,0,3) !(0,0,0)")); //Line
    b->Do(Move("(0,0,3)")); //Line
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2);

    //BoardAdvanced and BoardBasic respond to the creation of a square
    a->Set(Coordinat("(0,3,1)")); //Square
    b->Set(Coordinat("(0,3,1)")); //Square
    BOOST_CHECK(a->GetCurrentTurn() == Player::player2); //No toggle
    BOOST_CHECK(b->GetCurrentTurn() == Player::player2); //No toggle
    BOOST_CHECK(a->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    BOOST_CHECK(b->GetCurrentMove()->GetMustRemove() != MustRemoveState::no);
    BOOST_CHECK(a->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    BOOST_CHECK(b->CanRemove(std::vector<Coordinat>(1,Coordinat("(0,3,0)"))));
    a->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    b->Remove(std::vector<Coordinat>(1,Coordinat("(0,3,0)")));
    BOOST_CHECK(!a->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(!b->GetCurrentMove()->GetMustRemove());
    BOOST_CHECK(a->GetCurrentTurn() == Player::player1);
    BOOST_CHECK(b->GetCurrentTurn() == Player::player1);
  }


  //if (verbose) { TRACE("Test Game history"); }
  {
    // 12..
    // 34..
    // 56..
    // 7...
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    BOOST_CHECK(a->GetMoveHistory().empty());
    BOOST_CHECK(b->GetMoveHistory().empty());
    const std::vector<Move> v =
      {
        Move("(0,0,0)"),
        Move("(0,1,0)"),
        Move("(0,0,1)"),
        Move("(0,1,1)"),
        Move("(1,0,0)")
      };
    const std::size_t j = v.size();
    for (std::size_t i = 0; i!=j; ++i)
    {
      BOOST_CHECK(a->GetMoveHistory().size() == i);
      BOOST_CHECK(b->GetMoveHistory().size() == i);
      a->Do(v[i]);
      b->Do(v[i]);
      BOOST_CHECK(a->GetMoveHistory()[i] == v[i]);
      BOOST_CHECK(b->GetMoveHistory()[i] == v[i]);
    }
  }


  //if (verbose) { TRACE("Game test #1"); }
  {
    // 12..
    // 34..
    // 56..
    // 7...
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    a->Do(Move("(0,0,0)")); //1
    b->Do(Move("(0,0,0)"));
    a->Do(Move("(0,1,0)")); //2
    b->Do(Move("(0,1,0)"));
    a->Do(Move("(0,0,1)")); //3
    b->Do(Move("(0,0,1)"));
    a->Do(Move("(0,1,1)")); //4
    b->Do(Move("(0,1,1)"));
    a->Do(Move("(0,0,2)")); //5
    b->Do(Move("(0,0,2)"));
    a->Do(Move("(0,1,2)")); //6
    b->Do(Move("(0,1,2)"));
    BOOST_CHECK(!a->CanDo(Move("(0,0,3)"))); //7
    BOOST_CHECK( a->CanDo(Move("(0,0,3) !(0,0,3)"))); //7
    BOOST_CHECK( b->CanDo(Move("(0,0,3)")));
  }
  //if (verbose) { TRACE("Game test #2"); }
  {
    // ....
    // ....
    // ....
    // ....
    //Test that in basic play, no marbles must be removed. Test that in advanced play, marbles must be removed.
    boost::shared_ptr<Game> a = CreateAdvancedGame();
    boost::shared_ptr<Game> b = CreateBasicGame();
    const std::vector<Move> v =
      {
        Move("(0,0,0)"), Move("(0,0,1)"), Move("(0,1,1)"), Move("(0,1,0)"),
        Move("(1,0,0)"), Move("(0,0,2)"), Move("(0,1,2)"), Move("(0,2,0)"),
        Move("(0,2,2)"), Move("(0,3,0)")
      };
    std::for_each(v.begin(),v.end(),
      [a,b](const Move& m)
      {
        BOOST_CHECK(a->CanDo(m));
        BOOST_CHECK(b->CanDo(m));
        a->Do(m);
        b->Do(m);
      }
    );
    BOOST_CHECK(!a->CanDo(Move("(0,2,1)")));
    BOOST_CHECK(!a->CanDo(Move("(0,2,1) !(0,0,0)")));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0)")));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)")));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)")));
    BOOST_CHECK(!a->CanDo(Move("(0,2,1) !(0,1,1)")));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)")));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)")));

    BOOST_CHECK(!b->CanDo(Move("(0,2,1)")));
    BOOST_CHECK(!b->CanDo(Move("(0,2,1) !(0,0,0)")));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0)")));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)")));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)")));
    BOOST_CHECK(!b->CanDo(Move("(0,2,1) !(0,1,1)")));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)")));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)")));
  }
  if (testing_depth < 2) return;

  //if (verbose) { TRACE("Playing 5 random basic Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomGame(CreateBasicBoard());
  }
  //if (verbose) { TRACE("Playing 5 random advanced Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomGame(CreateAdvancedBoard());
  }
  //if (verbose) { TRACE("Playing 5 random Pylos games"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomGame();
  }
}

