#ifndef __VB_IA__
#define __VB_IA__

#include <string>
#include "Player.hh"
using namespace std;

class IA : Player
{
 public:
  IA(string nom,int id);
  Coup getCoup(State etat);
};

#else
class IA : Player;
#endif
