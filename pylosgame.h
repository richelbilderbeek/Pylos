#ifndef PYLOSGAME_H
#define PYLOSGAME_H

#include <iosfwd>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "pylosboard.h"
#include "pyloscurrentmovestate.h"
#include "pylosfwd.h"
#include "pylosplayer.h"
#include "pylospositionstate.h"
#include "pyloswinner.h"

namespace ribi {
namespace pylos {

///Pylos is a class for storing a Pylos game.
///Games can be player in:\n
///- Pylos notation: (Can)Do\n
///- using Coordinats: (Can)Place, (Can)Move, (Can)Remove\n
///Games can also be saved and loaded.
struct Game
{
  ///Copy constructor
  Game(const Game& rhs);

  ///Create an Pylos game in the starting position.
  Game(const boost::shared_ptr<Board>& board);

  ///Create a mid-game Pylos.
  Game(
    const boost::shared_ptr<Board>& board,
    const Player current_player,
    const std::vector<pylos::Move>& move_history,
    const boost::shared_ptr<CurrentMoveState>& current_move);

  ///CanDo determines if a Pylos notation move is valid
  bool CanDo(const std::string& s) const;

  ///CanDo determines if a Pylos move is valid
  bool CanDo(const pylos::Move& m) const;

  ///CanRemove specifies if current player can remove one or
  ///two marble(s) at the requested position(s).
  bool CanRemove(const std::vector<Coordinat>& v) const;

  ///CanSet tests if the current player can be set at the Coordinat
  bool CanSet(const Coordinat& c) const;

  ///CanTransfer specifies if current player can transfer
  ///the marble at the specified coordinat for movement
  bool CanTransfer(const Coordinat& c) const;

  ///CanTransfer specifies if current player can transfer his marble
  ///to a new, higher position
  bool CanTransfer(
    const Coordinat& from,
    const Coordinat& to) const;

  ///Do performs a move in Pylos notation
  void Do(const std::string& s);

  ///Do performs a Pylos move
  void Do(const Move& m);

  ///GetAllPossibleMoves returns all moves valid for the active player
  const std::vector<Move> GetAllPossibleMoves() const noexcept;

  ///GetBoard returns the board.
  const boost::shared_ptr<Board>& GetBoard() const noexcept { return m_board; }

  ///Obtain the current move's state
  const boost::shared_ptr<CurrentMoveState> GetCurrentMove() const noexcept { return m_current_move; }

  ///GetCurrentTurn returns whose turn it is now
  Player GetCurrentTurn() const noexcept;

  const std::vector<pylos::Move>& GetMoveHistory() const noexcept
  {
    return m_move_history;
  }

  ///MustRemove returns whether the current player
  ///must remove one or two marbles
  MustRemoveState GetMustRemove() const noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///GetWinner returns the winner.
  Winner GetWinner() const noexcept;

  ///IsValid returns if the current Pylos game is valid
  //bool IsValid() const; //?Not used?

  ///Load loads a game in Pylos notation
  //void Load(const std::string& s) = 0;

  ///Remove lets the current player remove one or two marbles
  void Remove(const std::vector<Coordinat>& v);

  ///Restart sets the game in its initial position.
  void Restart();

  ///Set makes m_current_players place his marble
  ///at the specified position. After Place,
  ///MustRemoveMarbles must be called to determine if
  ///the current player must remove some marbles
  void Set(const Coordinat& c);


  ///ToStr converts Game its contents to a std::string
  //const std::string ToStr() const = 0;

  ///Transfer lets current player tranfer his marble to a new, higher position
  void Transfer(
    const Coordinat& from,
    const Coordinat& to);

  private:
  Game() = delete;
  ~Game() noexcept {}
  friend void boost::checked_delete<>(      Game*);
  friend void boost::checked_delete<>(const Game*);

  boost::shared_ptr<Board> m_board;
  boost::shared_ptr<CurrentMoveState> m_current_move;
  Player m_current_player;
  std::vector<pylos::Move> m_move_history;

  ///CanRemove specifies if current player can remove
  ///the marble at the requested position.
  bool CanRemove(const Coordinat& c) const;

  ///Remove lets the current player remove one marble.
  void Remove(const Coordinat& c);

  ///TogglePlayer toggles between player1 and player2 and saves the current
  ///move to the move history
  void TogglePlayer();

  friend bool operator==(const Game& lhs, const Game& rhs);
};

bool operator==(const Game& lhs, const Game& rhs);
bool operator!=(const Game& lhs, const Game& rhs);
std::ostream& operator<<(std::ostream& os,const Game& p);

///CanLoadPylos determines if loading a Pylos game from file
///will be successfull
bool CanLoadPylos(const std::string& filename);

///Create an advanced game at its initial position
boost::shared_ptr<Game> CreateAdvancedGame();

///Create a basic game at its initial position
boost::shared_ptr<Game> CreateBasicGame();

///LoadPylos loads a Pylos game from file
boost::shared_ptr<Game> LoadPylos(const std::string& filename);

///PlayRandomPylosGame plays a random Pylos game and returns the winner.
Winner PlayRandomGame(const boost::shared_ptr<Board>& board = boost::shared_ptr<Board>());

} //~namespace Pylos
} //~namespace ribi

#endif // PYLOSGAME_H
