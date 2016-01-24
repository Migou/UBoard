#include "Coup.hh"
#include "utils.hh"
#include "Action.hh"
using namespace std;

Coup::Coup()
{
  this->actionList = new vector<Action*>();
}
/*Coup::Coup(Coup* c)
{
  // constructeur de copie
  this->actionList = new vector<Action*>();
  for(int i=0;i<c->actionList->size();i++)
  {
    this->actionList[i] = c->actionList[i]->clone();
  }
  }*/
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
