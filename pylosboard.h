#ifndef PYLOSBOARD_H
#define PYLOSBOARD_H

#include <vector>



#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include "pylosfwd.h"
#include "pylosmove.h"
#include "pyloswinner.h"
#include "pylosplayer.h"
#include "pylospositionstate.h"


namespace ribi {

struct TextCanvas;

namespace pylos {

struct Board
{
  typedef std::vector<std::vector<PositionState> > Layer;

  Board() noexcept;
  virtual ~Board() noexcept;

  ///CanDo determines if a Pylos notation move is valid
  bool CanDo(const std::string& s, const Player player) const;

  ///CanDo determines if a Pylos move is valid
  bool CanDo(const Move& m, const Player player) const;

  ///CanDoSomething specifies if there is a possible move to do for a player
  bool CanDoSomething(const Player& player) const;

  ///CanRemove specifies if one or
  ///two marble(s) can be removed at the requested position(s).
  bool CanRemove(const std::vector<Coordinat>& v, const Player player) const;

  ///CanMove specifies the marble at the specified coordinat can be tranferred
  bool CanTransfer(const Coordinat& c, const Player player) const;

  ///CanMove specifies if the marble can be tranferred to the new (higher) position
  bool CanTransfer(
    const Coordinat& from,
    const Coordinat& to, const Player player) const;

  ///CanSet specifies if a marble can be placed at the coordinat.
  ///It is chosen to let the client specify a player, to
  ///emphasise that a player's marble is placed, instead
  ///of a PositionState::empty
  bool CanSet(const Coordinat& c, const Player player) const;

  ///Clone a derived class of Board.
  virtual std::unique_ptr<Board> Clone() const = 0;

  ///Count counts the requested state at the specified coordinats
  int Count(const std::vector<Coordinat>& coordinats, const PositionState state) const;

  ///Count counts the requested state.
  ///Valid states are empty, player1 and player2
  int Count(const PositionState state) const;

  ///Do performs a move in Pylos notation
  void Do(const std::string& s, const Player player);

  ///Do performs a Pylos move
  void Do(const Move& m, const Player player);

  ///Get returns the state of the requested location
  PositionState Get(const Coordinat& c) const noexcept;

  ///GetAllPossibleMoves returns all moves valid for the selected player
  const std::vector<Move> GetAllPossibleMoves(const Player& player) const noexcept;

  ///GetLayerSize returns how many marbles this is wide/height.
  ///For example; layer 0 has 4x4 marbles, so GetLayerSize
  ///will return 4.
  int GetLayerSize(const int layer) const noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Return the possible winner
  Winner GetWinner() const noexcept;

  ///Remove removes one or two marbles.
  void Remove(const std::vector<Coordinat>& v, const Player player);

  ///Restart sets the board in its initial position.
  void Restart();

  ///Set sets the state of the given location.
  ///must_remove is set to the MustRemoveState who must remove one or two marbles.
  virtual void Set(
    const Coordinat& c,
    const Player player,
    MustRemoveState& must_remove
  ) = 0;


  ///Display the board as a std::string
  std::string ToStr() const noexcept;

  ///Display the board as a 2D std::string
  std::vector<std::string> ToText() const noexcept;

  ///Display the board as a 2D std::string
  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;

  ///Transfer lets current player transfer his marble to a new, higher position
  void Transfer(
    const Coordinat& from,
    const Coordinat& to,
    MustRemoveState& must_remove);


  protected:

  ///m_board holds the board structure.\n
  ///m_board[0]: bottom 4x4 layer\n
  ///m_board[1]: 3x3 layer\n
  ///m_board[2]: 2x2 layer\n
  ///m_board[3]: top 1x1 layer
  std::vector<Layer> m_board;

  ///CanRemove specifies if current player can remove
  ///the marble at the requested position.
  bool CanRemove(const Coordinat& c, const Player player) const;

  ///RemoveMarble removes one marble.
  void Remove(const Coordinat& c, const Player player);

  private:
  ///CreateEmptyBoard created an empty board.
  std::vector<Layer> CreateEmptyBoard() const noexcept;

  ///CreateLayer creates an empty layer.
  const Layer CreateLayer(const int sz) const;

  //Friends
  //friend void boost::checked_delete<>(Board* x);
  friend bool operator==(const Board& lhs, const Board& rhs) noexcept;
};

///A BoardAdvanced lets a player remove one or two marbles when
///- a player creates a 2x2 square of marbles of his/her color
///- a player creates a 1x4 (bottom layer) or 1x3 (one-but-bottom layer)
///  line of marbles of his/her color
struct BoardAdvanced final : public Board
{
  BoardAdvanced() noexcept;
  ~BoardAdvanced() noexcept;

  ///Clone a derived class of Board.
  std::unique_ptr<Board> Clone() const noexcept override;

  ///Load loads a game in Pylos notation
  //void Load(const std::string& s);

  ///Save saves the current game in Pylos notation
  //void Save(const std::string& s) const;

  ///ToStr converts Pylos its contents to a std::string
  //const std::string ToStr() const;

  private:
  ///Set sets the state of the given location.
  ///must_remove is set to true if the current player is allowed
  ///to remove one or two marbles.
  void Set(
    const Coordinat& c,
    const Player state,
    MustRemoveState& must_remove);
};

///A BoardBasic lets a player remove one or two marbles when
///- a player creates a 2x2 square of marbles of his/her color
struct BoardBasic final : public Board
{
  BoardBasic() noexcept;
  ~BoardBasic() noexcept;

  ///Clone a derived class of Pylos.
  std::unique_ptr<Board> Clone() const noexcept override;

  ///Load loads a game in Pylos notation
  //void Load(const std::string& s);

  ///Save saves the current game in Pylos notation
  //void Save(const std::string& s) const;

  ///ToStr converts Pylos its contents to a std::string
  //const std::string ToStr() const;

  private:
  ///Set sets the state of the given location.
  ///must_remove is set to true if the current player is allowed
  ///to remove one or two marbles.
  void Set(
    const Coordinat& c,
    const Player state,
    MustRemoveState& must_remove);
};

///A BoardBeginner lets a player remove one or two marbles when
///- never


///Create a BoardAdvanced
std::unique_ptr<Board> CreateAdvancedBoard() noexcept;

///Create a BoardBasic
std::unique_ptr<Board> CreateBasicBoard() noexcept;

///PlayRandomPylosGame plays a random Pylos game and returns the winner.
Winner PlayRandomPylosGame(const boost::shared_ptr<Board>& board_original = boost::shared_ptr<Board>()) noexcept;

bool operator==(const Board& lhs, const Board& rhs) noexcept;
bool operator!=(const Board& lhs, const Board& rhs) noexcept;
std::ostream& operator<<(std::ostream& os,const Board& p) noexcept;

} //~namespace Pylos
} //~namespace ribi

#endif // PYLOSBOARD_H
