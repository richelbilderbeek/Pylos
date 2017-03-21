#include "pylosboard.h"

#include <boost/test/unit_test.hpp>

#include "pylosmustremovestate.h"

using namespace ribi::pylos;

BOOST_AUTO_TEST_CASE(pylose_board)
{
  const int testing_depth = 1;

  //if (verbose) { TRACE("Test operator=="); }
  {
    boost::shared_ptr<BoardBasic> a(new BoardBasic);
    boost::shared_ptr<BoardBasic> b(new BoardBasic);
    BOOST_CHECK(*a == *b);
    a->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a == *b);
  }
  //Test operator==
  {
    boost::shared_ptr<BoardAdvanced> a(new BoardAdvanced);
    boost::shared_ptr<BoardAdvanced> b(new BoardAdvanced);
    BOOST_CHECK(*a == *b);
    a->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a == *b);
  }
  {
    boost::shared_ptr<BoardAdvanced> a(new BoardAdvanced);
    boost::shared_ptr<BoardBasic> b(new BoardBasic);
    BOOST_CHECK(*a != *b);
    a->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
  }
  //if (verbose) { TRACE("Test Game::Clone of GameBasic"); }
  {
    const boost::shared_ptr<Board> a(new BoardBasic);
    const boost::shared_ptr<Board> b(a->Clone());
    const boost::shared_ptr<Board> c(new BoardAdvanced);
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
    a->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(*a != *c);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
  }
  //if (verbose) { TRACE("Test Game::Clone of GameAdvanced"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    const boost::shared_ptr<Board> b(a->Clone());
    const boost::shared_ptr<Board> c(new BoardBasic);
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
    a->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a != *b);
    BOOST_CHECK(*a != *c);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(*a == *b);
    BOOST_CHECK(*a != *c);
  }
  //if (verbose) { TRACE("Test Clone of played GameBasic"); }
  {
    const boost::shared_ptr<Board> a(new BoardBasic);
    a->Do("(0,0,0)",Player::player1);
    const boost::shared_ptr<Board> b(a->Clone());
    BOOST_CHECK(*a == *b);
  }
  //if (verbose) { TRACE("Test Clone of played BoardAdvanced"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    a->Do("(0,0,0)",Player::player1);
    const boost::shared_ptr<Board> b(a->Clone());
    BOOST_CHECK(*a == *b);
  }
  //if (verbose) { TRACE("Test conversion of Board to text"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    const boost::shared_ptr<Board> b(new BoardBasic);
    a->Do("(0,0,0)",Player::player1);
    b->Do("(0,0,0)",Player::player1);
    BOOST_CHECK(a->ToStr() == std::string(
      "X . . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());
    a->Do("(0,1,0)",Player::player2);
    b->Do("(0,1,0)",Player::player2);
    BOOST_CHECK(a->ToStr() == std::string(
      "X O . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());

    a->Do("(0,1,1)",Player::player1);
    b->Do("(0,1,1)",Player::player1);
    //if (verbose) { TRACE(a->ToStr()); }
    BOOST_CHECK(a->ToStr() == std::string(
      "X O . .\n"
      " . . . \n"
      ". X . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());

    a->Do("(0,0,1)",Player::player2);
    b->Do("(0,0,1)",Player::player2);
    //if (verbose) { TRACE(a->ToStr()); }
    BOOST_CHECK(a->ToStr() == std::string(
      "X O . .\n"
      " . . . \n"
      "O X . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());

    a->Do("(1,0,0)",Player::player1);
    b->Do("(1,0,0)",Player::player1);
    //if (verbose) { TRACE(a->ToStr()); }
    BOOST_CHECK(a->ToStr() == std::string(
      "X O . .\n"
      " X . . \n"
      "O X . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());

    a->Do("(0,2,0)",Player::player2);
    b->Do("(0,2,0)",Player::player2);
    //if (verbose) { TRACE(a->ToStr()); }
    BOOST_CHECK(a->ToStr() == std::string(
      "X O O .\n"
      " X . . \n"
      "O X . .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());

    a->Do("(0,2,1)",Player::player1);
    b->Do("(0,2,1)",Player::player1);
    //if (verbose) { TRACE(a->ToStr()); }
    BOOST_CHECK(a->ToStr() == std::string(
      "X O O .\n"
      " X . . \n"
      "O X X .\n"
      " . . . \n"
      ". . . .\n"
      " . . . \n"
      ". . . ."));
    BOOST_CHECK(a->ToStr() == b->ToStr());
  }
  //if (verbose) { TRACE("Test horizontal detection of line in both boards"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    const boost::shared_ptr<Board> b(new BoardBasic);
    MustRemoveState must_remove = MustRemoveState::no;
    a->Set(Coordinat("(0,0,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,1,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,1,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,3,0)"),Player::player1,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,3,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove); //Basic does not test for lines

    a->Set(Coordinat("(0,0,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,1,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,1,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,3,2)"),Player::player2,must_remove); BOOST_CHECK(must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,3,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove); //Basic does not test for lines
  }
  //if (verbose) { TRACE("Test horizontal detection of line in both boards"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    const boost::shared_ptr<Board> b(new BoardBasic);
    MustRemoveState must_remove = MustRemoveState::no;
    a->Set(Coordinat("(0,2,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,1)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,1)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,2)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,2)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,3)"),Player::player1,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,2,3)"),Player::player1,must_remove); BOOST_CHECK(!must_remove); //Basic does not test for lines

    a->Set(Coordinat("(0,0,0)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,0)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,0,1)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,1)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,0,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,0,3)"),Player::player2,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,0,3)"),Player::player2,must_remove); BOOST_CHECK(!must_remove); //Basic does not test for lines
  }
  //if (verbose) { TRACE("Test block detection of line in both boards"); }
  {
    const boost::shared_ptr<Board> a(new BoardAdvanced);
    const boost::shared_ptr<Board> b(new BoardBasic);
    MustRemoveState must_remove = MustRemoveState::no;
    a->Set(Coordinat("(0,0,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,1,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,1,0)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,0,1)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,0,1)"),Player::player1,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,1,1)"),Player::player1,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,1,1)"),Player::player1,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);

    a->Set(Coordinat("(0,3,3)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,3,3)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,3,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,3,2)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,3)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    b->Set(Coordinat("(0,2,3)"),Player::player2,must_remove); BOOST_CHECK(!must_remove);
    a->Set(Coordinat("(0,2,2)"),Player::player2,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
    b->Set(Coordinat("(0,2,2)"),Player::player2,must_remove); BOOST_CHECK( must_remove != MustRemoveState::no);
  }
  //if (verbose) { TRACE("Board test transfer of marbles"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    a->Do(Move("(0,0,0)"),Player::player1);
    b->Do(Move("(0,0,0)"),Player::player1);
    BOOST_CHECK(!a->CanDo(Move("(0,0,0)"),Player::player1));
    BOOST_CHECK(!b->CanDo(Move("(0,0,0)"),Player::player1));
    BOOST_CHECK(!a->CanDo(Move("(0,0,0)"),Player::player2));
    BOOST_CHECK(!b->CanDo(Move("(0,0,0)"),Player::player2));
    BOOST_CHECK(!a->CanDo(Move("(0,0,0)->(0,0,1)"),Player::player1));
    BOOST_CHECK(!b->CanDo(Move("(0,0,0)->(0,0,1)"),Player::player1));
    BOOST_CHECK(!a->CanDo(Move("(0,0,0)->(0,0,1)"),Player::player2));
    BOOST_CHECK(!b->CanDo(Move("(0,0,0)->(0,0,1)"),Player::player2));
  }
  //if (verbose) { TRACE("Board test stacking by setting"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    const std::vector<Coordinat> v =
      {
        Coordinat("(0,0,0)"), Coordinat("(0,1,0)"), Coordinat("(0,2,0)"), Coordinat("(0,3,0)"),
        Coordinat("(0,3,1)"), Coordinat("(0,2,1)"), Coordinat("(0,1,1)"), Coordinat("(0,0,1)"),
        Coordinat("(0,0,2)"), Coordinat("(0,1,2)"), Coordinat("(0,2,2)"), Coordinat("(0,3,2)"),
        Coordinat("(0,3,3)"), Coordinat("(0,2,3)"), Coordinat("(0,1,3)"), Coordinat("(0,0,3)"),
        Coordinat("(1,0,0)"), Coordinat("(1,1,0)"), Coordinat("(1,2,0)"),
        Coordinat("(1,0,1)"), Coordinat("(1,1,1)"), Coordinat("(1,2,1)"),
        Coordinat("(1,0,2)"), Coordinat("(1,1,2)"), Coordinat("(1,2,2)"),
        Coordinat("(2,0,0)"), Coordinat("(2,1,0)"),
        Coordinat("(2,0,1)"), Coordinat("(2,1,1)"),
        Coordinat("(3,0,0)")
      };
    Player player = Player::player1;
    std::for_each(v.begin(),v.end(),
      [a,b,&player](const Coordinat& c)
      {
        MustRemoveState must_remove = MustRemoveState::no;
        BOOST_CHECK(a->CanSet(c,player));
        BOOST_CHECK(b->CanSet(c,player));
        a->Set(c,player,must_remove); BOOST_CHECK(!must_remove);
        b->Set(c,player,must_remove); BOOST_CHECK(!must_remove);
        Toggle(player);
      }
    );
    BOOST_CHECK(a->GetWinner() != Winner::none);
    BOOST_CHECK(b->GetWinner() != Winner::none);
  }

  //if (verbose) { TRACE("Board test #2"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    const std::vector<Move> v =
      {
        Move("(0,0,0)"), Move("(0,0,1)"), Move("(0,1,1)"), Move("(0,1,0)"),
        Move("(1,0,0)"), Move("(0,0,2)"), Move("(0,1,2)"), Move("(0,2,0)"),
        Move("(0,2,2)"), Move("(0,3,0)")
      };
    Player player = Player::player1;
    std::for_each(v.begin(),v.end(),
      [a,b,&player](const Move& m)
      {
        BOOST_CHECK(a->CanDo(m,player));
        BOOST_CHECK(b->CanDo(m,player));
        a->Do(m,player);
        b->Do(m,player);
        Toggle(player);
      }
    );
    BOOST_CHECK(!a->CanDo(Move("(0,2,1)"),Player::player1));
    BOOST_CHECK(!a->CanDo(Move("(0,2,1) !(0,0,0)"),Player::player1));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0)"),Player::player1));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)"),Player::player1));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)"),Player::player1));
    BOOST_CHECK(!a->CanDo(Move("(0,2,1) !(0,1,1)"),Player::player1));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)"),Player::player1));
    BOOST_CHECK( a->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)"),Player::player1));

    BOOST_CHECK(!b->CanDo(Move("(0,2,1)"),Player::player1));
    BOOST_CHECK(!b->CanDo(Move("(0,2,1) !(0,0,0)"),Player::player1));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0)"),Player::player1));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(0,0,0) !(1,0,0)"),Player::player1));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,0,0)"),Player::player1));
    BOOST_CHECK(!b->CanDo(Move("(0,2,1) !(0,1,1)"),Player::player1));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(0,1,1) !(1,0,0)"),Player::player1));
    BOOST_CHECK( b->CanDo(Move("(0,2,1) !(1,0,0) !(0,1,1)"),Player::player1));
  }

  //if (verbose) { TRACE("Board test #3"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    const std::vector<Move> v =
      {
        Move("(0,0,0)"), Move("(0,1,0)"), Move("(0,0,1)"), Move("(0,1,1)"),
        Move("(0,0,2)"), Move("(0,1,2)")
      };
    Player player = Player::player1;
    std::for_each(v.begin(),v.end(),
      [a,b,&player](const Move& m)
      {
        BOOST_CHECK(a->CanDo(m,player));
        BOOST_CHECK(b->CanDo(m,player));
        a->Do(m,player);
        b->Do(m,player);
        Toggle(player);
      }
    );

    BOOST_CHECK( a->CanDo(Move("(0,0,2)->(1,0,0)"),Player::player1)); //1
    BOOST_CHECK(!a->CanDo(Move("(0,0,1)->(1,0,1)"),Player::player1)); //2
    BOOST_CHECK(!a->CanDo(Move("(0,0,0)->(0,2,0)"),Player::player1)); //3

    BOOST_CHECK( b->CanDo(Move("(0,0,2)->(1,0,0)"),Player::player1)); //1
    BOOST_CHECK(!b->CanDo(Move("(0,0,1)->(1,0,1)"),Player::player1)); //2
    BOOST_CHECK(!b->CanDo(Move("(0,0,0)->(0,2,0)"),Player::player1)); //3
  }


  //if (verbose) { TRACE("Test ribi::pylos::Board::GetAllPossibleMoves simple transfer"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player1).size() == 16);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player1).size() == 16);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player2).size() == 16);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player2).size() == 16);
    a->Do(Move("(0,0,0)"),Player::player1); //1
    b->Do(Move("(0,0,0)"),Player::player1);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player1).size() == 15);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player1).size() == 15);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player2).size() == 15);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player2).size() == 15);
    a->Do(Move("(0,0,1)"),Player::player2); //2
    b->Do(Move("(0,0,1)"),Player::player2);
    a->Do(Move("(0,1,1)"),Player::player1); //3
    b->Do(Move("(0,1,1)"),Player::player1);
    a->Do(Move("(0,1,0)"),Player::player2); //4
    b->Do(Move("(0,1,0)"),Player::player2);
    BOOST_CHECK(a->Count(PositionState::player1) == 2);
    BOOST_CHECK(b->Count(PositionState::player1) == 2);
    BOOST_CHECK(a->Count(PositionState::player2) == 2);
    BOOST_CHECK(b->Count(PositionState::player2) == 2);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player1).size() == 13); //13
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player1).size() == 13); //12 on bottom layer
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player2).size() == 13); //1 on one-but-buttom layer
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player2).size() == 13);
    a->Do(Move("(0,2,0)"),Player::player1);
    b->Do(Move("(0,2,0)"),Player::player1);
    a->Do(Move("(0,2,1)"),Player::player2);
    b->Do(Move("(0,2,1)"),Player::player2);
    BOOST_CHECK(a->Get(Coordinat(0,2,1)) == PositionState::player2);
    BOOST_CHECK(b->Get(Coordinat(0,2,1)) == PositionState::player2);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player1).size() == 14); //13
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player1).size() == 14); //10 on bottom layer
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player2).size() == 14); //2 on one-but-buttom layer
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player2).size() == 14); //2 transfers
  }
  //if (verbose) { TRACE("Test ribi::pylos::Board::GetAllPossibleMoves simple remove"); }
  {
    boost::shared_ptr<Board> a = CreateAdvancedBoard();
    boost::shared_ptr<Board> b = CreateBasicBoard();
    a->Do(Move("(0,0,0)"),Player::player1);
    b->Do(Move("(0,0,0)"),Player::player1);
    a->Do(Move("(0,0,1)"),Player::player1);
    b->Do(Move("(0,0,1)"),Player::player1);
    a->Do(Move("(0,1,0)"),Player::player1);
    b->Do(Move("(0,1,0)"),Player::player1);
    //After placing (0,1,1), there are one (4 ways) or two marbles (6 ways) to be removed
    //Next to this, there are 12 empty spots
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player1).size() == 22);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player1).size() == 22);
    BOOST_CHECK(a->GetAllPossibleMoves(Player::player2).size() == 13);
    BOOST_CHECK(b->GetAllPossibleMoves(Player::player2).size() == 13);
  }

  if (testing_depth < 2) return;

  //if (verbose) { TRACE("Filling up 5 basic Pylos boards randomly"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomPylosGame(CreateBasicBoard());
  }
  //if (verbose) { TRACE("Filling up 5 advanced Pylos boards randomly"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomPylosGame(CreateAdvancedBoard());
  }
  //if (verbose) { TRACE("Filling up 5 Pylos boards randomly"); }
  for (int i=0; i!=5; ++i)
  {
    PlayRandomPylosGame();
  }
}
