#ifndef _vb_action_
#define _vb_action_

#include "State.hh"
#include <string>
using namespace std;

class Action {
public:
  //  virtual State execute(State)=0; 
  virtual Action* getInverse()=0;
  virtual void execute_mod(State*)=0; 
  virtual string toString()=0; 
  virtual Action* clone()=0; 
  //virtual Action* cloneAction()=0; // retourne un nouvel objet ActionXXX* carté en Action*
};

#else
class Action;
#endif
