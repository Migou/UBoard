#ifndef __VB_COUP_
#define __VB_COUP_

#include <vector>
#include "Action.hh"
#include "ActionAllumettes.hh"
using namespace std;

class Coup
{
 public : 
  Coup();
  Coup(int i);
  vector<Action*>* actionList;
  string toString();

  //State execute(State currentState); // NON, on utilise State::State(Coup)
};

#else
class Coup;
#endif
