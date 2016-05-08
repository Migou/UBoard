#include "ActionAllumettes.hh"
#include <string>
using namespace std;

ActionAllumettes::ActionAllumettes(int nbpris)
{
  this->pris = nbpris;
}

Action* ActionAllumettes::clone()
{
  ActionAllumettes* res = new ActionAllumettes(this->pris);
  return (Action*)res;
} 

// TODO : normalement, les actions
/*State ActionAllumettes::execute(State currentState)
{
  die("obsolete, utiliser execute_mod");
  int nbal = currentState.getNbAllumettes();
  State newstate(currentState);
  if(nbal - this->pris < 0) die("fatal error"); 

  newstate.setNbAllumettes(nbal - this->pris);
  return newstate;
  }*/

void ActionAllumettes::execute_mod(State* currentState)
{
  int nbal = currentState->getNbAllumettes();
  if(nbal - this->pris < 0) die("fatal error 4"); 
  currentState->setNbAllumettes(nbal - this->pris);
}

Action* ActionAllumettes::getInverse(){
  return (Action*)new ActionAllumettes(-this->pris);
}

string ActionAllumettes::toString()
{
  return my_int_to_string(this->pris);
}

