#ifndef PYLOSWINNER_H
#define PYLOSWINNER_H

#include <string>

namespace ribi {

namespace pylos {

enum class Winner { player1, player2, none };
std::string ToStr(const Winner winner);

} //~namespace Pylos
} //~namespace ribi

#endif // PYLOSWINNER_H
