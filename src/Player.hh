#ifndef __VB_PLAYER__
#define __VB_PLAYER__

#include "Coup.hh"
#include "State.hh"
using namespace std;

class Player
{
 private:
  string nom;
  int id;
 public:
  Player(string nom,int id);
  virtual Coup getCoup(State s)=0; // virtual!!! mais ca compile pas. for human players, this function will wait for the user's (gui) action.
  string toString();

  // for IA players, will launch the artificial intelligence.
  // Migou : WtF does it mean?
  //int getId();

  /*  string getName();
  string toString(); // retourne <nom>(<id>) par exemple
  */
};

//int idjoueur(Player* p_p);

#else
 class Player;
//int idjoueur(Player*);
#endif
