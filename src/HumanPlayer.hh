#ifndef __VB_HUMANPLAYER__
#define __VB_HUMANPLAYER__

#include <string>
#include "Player.hh"
using namespace std;

class HumanPlayer : Player
{
 public:
  HumanPlayer(string nom,int id);
  Coup getCoup(State etat);
};

#else
class HumanPlayer : Player;
#endif
