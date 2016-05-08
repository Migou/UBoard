#ifndef __VB_ACTIONALLUMETTES__
#define __VB_ACTIONALLUMETTES__

#include <string>
#include "State.hh"
#include "Action.hh"
using namespace std;


class ActionAllumettes : Action
{
private:
  int pris;
public:
  ActionAllumettes(int nbpris);
  //State execute(State currentState);
  void execute_mod(State* currentState);
  Action* getInverse();
  Action* clone();
  //Action* cloneAction(); 
  string toString();
};

#else
  class ActionAllumettes;
#endif
