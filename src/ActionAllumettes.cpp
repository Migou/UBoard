#include "ActionAllumettes.hh"
#include <string>
using namespace std;

ActionAllumettes::ActionAllumettes(int nbpris)
{
  this->pris = nbpris;
}

/*Action* ActionAllumette::cloneAction()
{
  ActionAllumettes* res = new ActionAllumettes(this->nbpris);
  return (Action*)res;
  } */

// TODO : normalement, les actions
State ActionAllumettes::execute(State currentState)
{
  int nbal = currentState.getNbAllumettes();
  State newstate(currentState);
  if(nbal - this->pris < 0) die("fatal error"); 

  newstate.setNbAllumettes(nbal - this->pris);
  return newstate;
}

string ActionAllumettes::toString()
{
  return my_int_to_string(this->pris);
}
