#include "Coup.hh"
#include "utils.hh"
#include "Action.hh"
using namespace std;

Coup::Coup()
{
  this->actionList = new vector<Action*>();
}

Coup::Coup(Coup* c)
{
  // constructeur de copie
  this->actionList = new vector<Action*>();
  for(unsigned int i=0;i<c->actionList->size();i++)
  {
    Action* a = (*(c->actionList))[i];
    this->actionList->push_back( a->clone() );
  }
}
Coup::Coup(int i) // fonction à effacer. uniquement pour tester le jeu des allumettes
{
  ActionAllumettes* paa = new ActionAllumettes(i);
  this->actionList = new vector<Action*>();
  this->actionList->push_back((Action*)paa);
}


string Coup::toString()
{
  string res = "" ;
  for(int i=0;i<(int)this->actionList->size();i++)
  {
    res = res + (*this->actionList)[i]->toString() + ";" ;
  }
  return res;
}

void Coup::addAction(Action* a)
{
  this->actionList->push_back(a);
}

//!\\ cette methode ne devrait être utilisée que pour la créatioçn d'anticoups.
// les anticoups sont des coups représentatnl es opérations à effectuer pour défaire un coup précédemment joué
// ces anti-coups sont stockés dans un pile, ici : State::rollback_stack
void Coup::addActionFirst(Action* a)
{
  //v->insert(v->begin(),1);
  this->actionList->insert(this->actionList->begin(),a);
}
