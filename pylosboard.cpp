#pragma GCC diagnostic push

#include "pylosboard.h"

#include "pyloscoordinat.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"
#include "pylosplayer.h"
#include "pylospositionstate.h"
#include "pyloswinner.h"
#include "textcanvas.h"

#include <boost/numeric/conversion/cast.hpp>

#ifdef PYLOSGAME_H
#error pylos::Game must not be defined for a pylos::Board
#endif

#pragma GCC diagnostic pop

ribi::pylos::Board::Board() noexcept
  : m_board(CreateEmptyBoard())
{
  //Assume correct board sizes
  assert(m_board.size() == 4);
  assert(m_board[0].size() == 4);
  assert(m_board[0][0].size() == 4);
  assert(m_board[0][1].size() == 4);
  assert(m_board[0][2].size() == 4);
  assert(m_board[0][3].size() == 4);
  assert(m_board[1].size() == 3);
  assert(m_board[1][0].size() == 3);
  assert(m_board[1][1].size() == 3);
  assert(m_board[1][2].size() == 3);
  assert(m_board[2].size() == 2);
  assert(m_board[2][0].size() == 2);
  assert(m_board[2][1].size() == 2);
  assert(m_board[3].size() == 1);
  assert(m_board[3][0].size() == 1);
}

ribi::pylos::Board::~Board()
{
  //OK
}

bool ribi::pylos::Board::CanDo(const pylos::Move& m, const Player player) const
{
  assert(m.IsValid());
  if (m.m_move.size()==1)
  {
    //Placement
    if (!CanSet(m.m_move[0],player)) return false;
  }
  else
  {
    assert(m.m_move.size() == 2);
    if (!CanTransfer(m.m_move[0],m.m_move[1],player)) return false;
  }
  //Make a copy Pylos
  boost::shared_ptr<Board> p = Clone();
  assert(p && "Assume cloning succeeded");
  assert(p.get() != this && "Assume clone is in different memory location");
  assert(*p == *this && "Assumes clone is identical");
  //Do the move
  MustRemoveState must_remove = MustRemoveState::no;
  if (m.m_move.size()==1)
  {
    p->Set(m.m_move[0],player,must_remove);
  }
  else
  {
    p->Transfer(m.m_move[0],m.m_move[1],must_remove);
  }
  //Check if marbles need to be removed
  if (must_remove != MustRemoveState::no)
  {
    //Move must not lack one/two marbles to be removed
    if (m.m_remove.empty()) return false;
    //Must remove marbles
    return p->CanRemove(m.m_remove,player);
  }
  else
  {
    //Must not remove marbles, so the move is valid if
    //m_remove is empty
    return m.m_remove.empty();
  }
}

bool ribi::pylos::Board::CanDo(const std::string& s, const Player player) const
{
  try
  {
    return CanDo(pylos::Move(s),player);
  }
  catch (std::exception& e)
  {
    return false;
  }
}

bool ribi::pylos::Board::CanDoSomething(const Player& player) const
{
  return !GetAllPossibleMoves(player).empty();
}

bool ribi::pylos::Board::CanRemove(const std::vector<Coordinat>& v, const Player player) const
{
  assert(v.size() == 1 || v.size() == 2);
  if (v.size() == 1) return CanRemove(v[0],player);
  assert(v.size() == 2);
  //Disallow selecting the same marble twice
  if (v[0] == v[1]) return false;
  //Disallow selecting empty spots
  if ( Get(v[0]) == PositionState::empty
    || Get(v[1]) == PositionState::empty) return false;
  //Disallow selecting marbles of different colors
  if (Get(v[0]) != Get(v[1])) return false;
  //Keep one ordering, c2 must be above c1
  if (v[0].GetLayer() == v[1].GetLayer())
  {
    return CanRemove(v[0],player) && CanRemove(v[1],player);
  }
  if (v[0].GetLayer() > v[1].GetLayer())
  {
    std::vector<Coordinat> w(v);
    std::swap(w[0],w[1]);
    return CanRemove(w,player);
  }
  //Assert proper ordering
  assert(v[0].GetLayer() < v[1].GetLayer());
  //If the top marble cannot be removed,
  //the lower cannot either
  if (!CanRemove(v[1],player)) return false;
  //The bottom marble can be removed if above are only empty spots, or only the top marble
  //Clone the board, remove the top marble of the clone and test if the bottom marble can be removed
  boost::shared_ptr<Board> b = this->Clone();
  assert(b->CanRemove(v[1],player));
  b->Remove(v[1],player);
  return b->CanRemove(v[0],player);
}

bool ribi::pylos::Board::CanRemove(const Coordinat& c, const Player player) const
{
  //Cannot remove an empty spot
  if (Get(c)==PositionState::empty) return false;

  //Cannot remove marble of another player
  if (Get(c)!=ToPositionState(player)) return false;

  //Cannot remove from top layer, because then the player at the top has already won
  if (c.GetLayer() == 3) return false;

  //A marble can be removed if all positions above are empty
  const std::vector<Coordinat> v = GetAbove(c);
  return Count(v,PositionState::empty) == static_cast<int>(v.size());
}

bool ribi::pylos::Board::CanTransfer(const Coordinat& c, const Player player) const
{
  //Cannot transfer an empty spot
  if (Get(c)==PositionState::empty) return false;

  //Cannot transfer marble of other color
  if (Get(c)!=ToPositionState(player)) return false;

  //Cannot transfer from top layer, because then the player at the top has already won
  if (c.GetLayer() == 3) return false;

  //A marble can be transferred if all positions above are empty
  const std::vector<Coordinat> v = GetAbove(c);
  return Count(v,PositionState::empty) == static_cast<int>(v.size());
}

bool ribi::pylos::Board::CanTransfer(const Coordinat& from,
  const Coordinat& to,
  const Player player) const
{
  //The source and target must differ
  if (from == to) return false;

  //The to position must be higher
  if (from.GetLayer() >= to.GetLayer()) return false;

  //The from position must be the player
  if (Get(from) != ToPositionState(player)) return false;

  //The to position must be empty
  if (Get(to) != PositionState::empty) return false;

  //Transfer the marble by cloning the board, removing it and placing it
  boost::shared_ptr<Board> b = this->Clone();

  assert(player == ToPlayer(b->Get(from))); //Added check for line below
  //const Player player = ToPlayer(b->Get(from)); //Removed

  assert(b->CanRemove(from,player));
  b->Remove(from,player);
  return b->CanSet(to,player);
}

#ifdef NDEBUG
bool ribi::pylos::Board::CanSet(const Coordinat& c, const Player) const
#else
bool ribi::pylos::Board::CanSet(const Coordinat& c, const Player player) const
#endif
{
  assert(player == Player::player1 || player == Player::player2); //Prevent compiler from complaining
  if (Get(c) != PositionState::empty) return false;
  //Player can always place a marble at an empty spot at the bottom
  if (c.GetLayer() == 0) return true;
  //Player wants to place a marbles at non-bottom layer,
  //which is valid if none of the spots below are empty
  const std::vector<Coordinat> v = GetBelow(c);
  assert(v.size() == 4);
  return Count(v,PositionState::empty) == 0;
}

int ribi::pylos::Board::Count(const std::vector<Coordinat>& coordinats, const PositionState state) const
{
  return std::count_if(coordinats.begin(),coordinats.end(),
    [this,state](const Coordinat& c)
    {
      return Get(c) == state;
    }
  );
}

int ribi::pylos::Board::Count(const PositionState state) const
{
  const std::vector<Coordinat> v = pylos::GetAllCoordinats();
  return Count(v,state);
}

std::unique_ptr<ribi::pylos::Board> ribi::pylos::CreateAdvancedBoard() noexcept
{
  #if __cplusplus >= 201402L //C++14
  return std::make_unique<BoardAdvanced>();
  #else
  std::unique_ptr<Board> b{new BoardAdvanced};
  return b;
  #endif
}

std::unique_ptr<ribi::pylos::Board> ribi::pylos::CreateBasicBoard() noexcept
{
  #if __cplusplus >= 201402L //C++14
  return std::make_unique<BoardBasic>();
  #else
  std::unique_ptr<Board> b{new BoardBasic};
  return b;
  #endif
}

std::vector<ribi::pylos::Board::Layer> ribi::pylos::Board::CreateEmptyBoard() const noexcept
{
  std::vector<Layer> v;
  v.push_back(CreateLayer(4));
  v.push_back(CreateLayer(3));
  v.push_back(CreateLayer(2));
  v.push_back(CreateLayer(1));
  return v;
}

const ribi::pylos::Board::Layer ribi::pylos::Board::CreateLayer(const int sz) const
{
  assert(sz > 0);
  return std::vector<std::vector<PositionState> > (
    sz,std::vector<PositionState>(sz,PositionState::empty));
}

void ribi::pylos::Board::Do(const std::string& s, const Player player)
{
  Do(pylos::Move(s),player);
}

void ribi::pylos::Board::Do(const pylos::Move& m, const Player player)
{
  assert(CanDo(m,player));
  MustRemoveState must_remove = MustRemoveState::no;
  if (m.m_move.size() == 1)
  {
    this->Set(m.m_move[0],player,must_remove);
  }
  else
  {
    Transfer(m.m_move[0],m.m_move[1],must_remove);
  }
  if (!m.m_remove.empty())
  {
    assert(must_remove != MustRemoveState::no);
    std::for_each(m.m_remove.begin(),m.m_remove.end(),
      [this,&must_remove,player](const Coordinat& c)
      {
        Remove(c,player);
      }
    );
  }
  else
  {
    assert(!must_remove);
  }
}

ribi::pylos::PositionState ribi::pylos::Board::Get(const Coordinat& c) const noexcept
{
  //Just checking, a constructed Coordinat should pass all asserts
  assert(c.IsValid());
  assert(c.IsValid());
  assert(c.GetLayer() < static_cast<int>(m_board.size()));
  assert(!m_board.empty());
  assert(c.GetX() < static_cast<int>(m_board[c.GetLayer()].size()));
  assert(!m_board[c.GetLayer()].empty());
  assert(c.GetY() < static_cast<int>(m_board[c.GetLayer()][c.GetX()].size()));
  return m_board[c.GetLayer()][c.GetX()][c.GetY()];
}

const std::vector<ribi::pylos::Move> ribi::pylos::Board::GetAllPossibleMoves(const Player& player) const noexcept
{
  const std::vector<Coordinat> v = pylos::GetAllCoordinats();
  std::vector<Move> w;
  const auto j = v.end();
  for (auto i = v.begin(); i!=j; ++i)
  {
    //Check for set
    if (this->CanSet(*i,player))
    {
      assert(this->Get(*i) == PositionState::empty);
      if (CanDo(i->ToStr(),player))
      {
        //Check for simple set (that is, without removal
        w.push_back(Move(i->ToStr()));
      }
      else
      {
        //Check first removal coordinat
        for (auto r1 = v.begin(); r1!=j; ++r1)
        {
          //Check one-marble remove
          if (CanDo(Move( {*i}, {*r1} ),player))
          {
            w.push_back(Move( {*i}, {*r1} ));
            //Check two-marble remove
            for (auto r2 = r1; r2!=j; ++r2)
            {
              if (r1 == r2) continue; //Checked by CanDo
              if (CanDo(Move( {*i}, {*r1,*r2} ),player)) w.push_back(Move( {*i}, {*r1,*r2} ));
            }
          }
        }
      }
    }
    //Check for transfer
    else if (this->CanTransfer(*i,player))
    {
      assert(this->Get(*i) == ToPositionState(player));
      for (auto to = i; to!=j; ++to)
      {
        if (CanDo(Move( {*i,*to}, {} ),player))
        {
          //Check for simple transfer (that is, without removal
          w.push_back(Move( {*i,*to}, {} ));
        }
        else
        {
          //Check first removal coordinat
          for (auto r1 = v.begin(); r1!=j; ++r1)
          {
            //Check one-marble remove
            if (CanDo(Move( {*i,*to}, {*r1} ),player))
            {
              w.push_back(Move( {*i,*to}, {*r1} ));
              //Check two-marble remove
              for (auto r2 = r1; r2!=j; ++r2)
              {
                if (r1 == r2) continue; //Checked by CanDo
                if (CanDo(Move( {*i,*to}, {*r1,*r2} ),player)) w.push_back(Move( {*i,*to}, {*r1,*r2} ));
              }
            }
          }
        }
      }
    }
  }
  return w;
}

int ribi::pylos::Board::GetLayerSize(const int layer) const noexcept
{
  assert(layer >= 0);
  assert(layer < boost::numeric_cast<int>(m_board.size()));
  return boost::numeric_cast<int>(m_board[layer].size());
}

std::string ribi::pylos::Board::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::Board::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2012-05-05: version 2.0: initial release version");
  return v;
}

ribi::pylos::Winner ribi::pylos::Board::GetWinner() const noexcept
{
  if (Get(Coordinat(3,0,0)) != PositionState::empty)
  {
    switch (Get(Coordinat(3,0,0)))
    {
      case PositionState::player1: return Winner::player1;
      case PositionState::player2: return Winner::player2;
      default: assert(!"Should not get here");
    }
  }
  if (Count(PositionState::player1)==15  && !CanDoSomething(Player::player1)) return Winner::player2;
  if (Count(PositionState::player2)==15  && !CanDoSomething(Player::player2)) return Winner::player1;
  return Winner::none;
}

ribi::pylos::Winner ribi::pylos::PlayRandomPylosGame(
  const boost::shared_ptr<Board>& board_original) noexcept
{
  boost::shared_ptr<Board> board;
  if (board_original)
  {
    board = board_original->Clone();
  }
  else
  {
    if ((std::rand() >> 4) % 2)
      board = CreateAdvancedBoard();
    else
      board = CreateBasicBoard();
  }
  Player player = Player::player1;

  while (1)
  {
    if (board->GetWinner() != Winner::none)
    {
      return board->GetWinner();
    }
    //Use random move from GetAllPossibleMoves
    const std::vector<Move> v = board->GetAllPossibleMoves(player);
    const int i = std::rand() % v.size();
    board->Do(v[i],player);
    //Do not always toggle the player
    if ((std::rand() >> 4) % 2) Toggle(player);
  }
}

#ifdef NDEBUG
void ribi::pylos::Board::Remove(const Coordinat& c, const Player)
#else
void ribi::pylos::Board::Remove(const Coordinat& c, const Player player)
#endif
{
  assert(CanRemove(c,player));
  m_board[c.GetLayer()][c.GetX()][c.GetY()] = PositionState::empty;
}

void ribi::pylos::Board::Remove(const std::vector<Coordinat>& v, const Player player)
{
  assert(CanRemove(v,player));
  //Proper ordering: v[0] must be marble above
  if (v.size() == 2 && v[0].GetLayer() < v[1].GetLayer())
  {
    std::vector<Coordinat> w(v);
    std::swap(w[0],w[1]);
    Remove(w,player);
    return;
  }
  //Assert proper ordering
  assert(v.size() == 1 || v[0].GetLayer() >= v[1].GetLayer());
  std::for_each(v.begin(),v.end(),
    [this,player](const Coordinat& c)
    {
      Remove(c,player);
    }
  );
}

std::string ribi::pylos::Board::ToStr() const noexcept
{
  const std::vector<std::string> v = this->ToText();
  std::string s;
  std::for_each(v.begin(),v.end(),[&s](const std::string& t) { s += t; s += '\n'; } );
  s.resize( s.size() - 1);
  return s;
}

std::vector<std::string> ribi::pylos::Board::ToText() const noexcept
{
  std::vector<std::string> v(7,std::string(7,' '));
  for (int layer = 0; layer!=4; ++layer)
  {
    for (int y=0; y!=4-layer; ++y)
    {
      for (int x=0; x!=4-layer; ++x)
      {
        const int x_co = layer + (x * 2);
        const int y_co = layer + (y * 2);
        const Coordinat c(layer,x,y);
        assert(c.GetX() == x);
        assert(c.GetY() == y);
        assert(c.GetLayer() == layer);
        const char c_old = v[y_co][x_co];
        const char c_new = ToChar(Get(c));
        //Higher empty positions must not overwrite occupied lower ones
        if (c_new == ToChar(PositionState::empty)
          && ( c_old == ToChar(PositionState::player1)
            || c_old == ToChar(PositionState::player2) ) )
        {
          continue;
        }
        v[y_co][x_co] = c_new;
      }
    }
  }
  return v;
}

boost::shared_ptr<ribi::TextCanvas> ribi::pylos::Board::ToTextCanvas() const noexcept
{
  boost::shared_ptr<TextCanvas> canvas {
    new TextCanvas(7,7)
  };
  for (int layer = 0; layer!=4; ++layer)
  {
    for (int y=0; y!=4-layer; ++y)
    {
      for (int x=0; x!=4-layer; ++x)
      {
        const int x_co = layer + (x * 2);
        const int y_co = layer + (y * 2);
        const Coordinat c(layer,x,y);
        assert(c.GetX() == x);
        assert(c.GetY() == y);
        assert(c.GetLayer() == layer);
        const char c_old = canvas->GetChar(x_co,y_co);
        const char c_new = ToChar(Get(c));
        //Higher empty positions must not overwrite occupied lower ones
        if (c_new == ToChar(PositionState::empty)
          && ( c_old == ToChar(PositionState::player1)
            || c_old == ToChar(PositionState::player2) ) )
        {
          continue;
        }
        canvas->PutChar(x_co,y_co,c_new);
      }
    }
  }

  return canvas;
}


void ribi::pylos::Board::Transfer(
    const Coordinat& from,
    const Coordinat& to,
    MustRemoveState& must_remove)
{
  const PositionState state = Get(from);
  assert(state!=PositionState::empty);
  const Player player = ToPlayer(state);
  assert(CanTransfer(from,player));
  assert(CanSet(to,player));
  assert(CanTransfer(from,to,player));
  Remove(from,player);
  Set(to,player,must_remove);
}

bool ribi::pylos::operator==(const Board& lhs, const Board& rhs) noexcept
{
  //Determine if types are equal
  if (typeid(lhs)!=typeid(rhs)) return false;

  return lhs.m_board == rhs.m_board;
}

bool ribi::pylos::operator!=(const Board& lhs, const Board& rhs) noexcept
{
  return !(lhs==rhs);
}

std::ostream& ribi::pylos::operator<<(std::ostream& os,const Board& p) noexcept
{
  os << p.ToStr();
  return os;
}

ribi::pylos::BoardAdvanced::BoardAdvanced() noexcept
  : Board()
{

}

ribi::pylos::BoardAdvanced::~BoardAdvanced()
{
  //OK
}

std::unique_ptr<ribi::pylos::Board> ribi::pylos::BoardAdvanced::Clone() const noexcept
{
  #if __cplusplus >= 201402L //C++14
  return std::make_unique<BoardAdvanced>(*this);
  #else
  std::unique_ptr<Board> b{new BoardAdvanced(*this)};
  return b;
  #endif
}

void ribi::pylos::BoardAdvanced::Set(
  const Coordinat& c,
  const Player player,
  MustRemoveState& must_remove)
{
  assert(CanSet(c,player));

  const PositionState state = ToPositionState(player);
  m_board[c.GetLayer()][c.GetX()][c.GetY()] = state;
  assert(Get(c)==state);

  must_remove = MustRemoveState::no;

  //Check for squares
  {
    typedef std::vector<Coordinat> Square;
    const std::vector<Square> v = GetSquares(c);
    assert(v.size() < 5);
    bool do_return = false;
    std::for_each(v.begin(),v.end(),
      [this,&do_return,state](const Square& s)
      {
        if (!do_return)
        {
          bool success = true;
          std::for_each(s.begin(),s.end(),
            [this,&success,state](const Coordinat& d)
            {
              if (success) { if (Get(d)!=state) { success = false; } }
            }
          );
          if (success) { do_return = true; }
        }
      }
    );
    if (do_return) { must_remove = ToMustRemoveState(player); return; }
  }
  //Check for lines
  {
    typedef std::vector<Coordinat> Line;
    const std::vector<Line> v = GetLines(c);
    ///There will be zero (layer 2 and 3)
    ///or two lines (layer 0 and 1)
    assert(v.size() == 0 || v.size() == 2);
    if (std::find_if(v.begin(),v.end(),
      [this,state](const Line& s)
      {
        return std::find_if(
          s.begin(),s.end(),
            [this,state](const Coordinat& d)
            {
              return Get(d)!=state;
            }
          ) == s.end();
      }
    ) != v.end()) { must_remove = ToMustRemoveState(player); return; }
  }

}

ribi::pylos::BoardBasic::BoardBasic() noexcept
  : Board()
{

}

ribi::pylos::BoardBasic::~BoardBasic()
{
  //OK
}

std::unique_ptr<ribi::pylos::Board> ribi::pylos::BoardBasic::Clone() const noexcept
{
  #if __cplusplus >= 201402L //C++14
  return std::make_unique<BoardBasic>(*this);
  #else
  std::unique_ptr<Board> b{new BoardBasic(*this)};
  return b;
  #endif
}

void ribi::pylos::BoardBasic::Set(
  const Coordinat& c,
  const Player player,
  MustRemoveState& must_remove)
{
  assert(CanSet(c,player));

  const PositionState state = ToPositionState(player);
  m_board[c.GetLayer()][c.GetX()][c.GetY()] = state;
  assert(Get(c)==state);

  //Check for squares
  {
    typedef std::vector<Coordinat> Square;
    const std::vector<Square> v = GetSquares(c);
    if (std::find_if(
      v.begin(),v.end(),
        [this,state](const Square& s)
        {
          return std::find_if(
            s.begin(),s.end(),
            [this,state](const Coordinat& d)
            {
              return Get(d) != state;
            }
          ) == s.end();
        }
      ) != v.end())
    {
      must_remove = ToMustRemoveState(player);
      return;
    }
  }
  must_remove = MustRemoveState::no;
  return;
}
