#include "State.hh"
#include "IA.hh"
#include "Player.hh"
#include "Coup.hh"
#include "HumanPlayer.hh"
#include "constants.hh"
#include "LuaCall.hh"
#include <stdlib.h>


// constructeur permettant de charge l'état initial à partir d'un fichier de conf lua
// post : le programmeur devra penser à ajouter des joueurs grâce à State::createPlayer
State::State(){
  // Version 1 : données représentées par un simple entier
  // this->nballumettes = NBAL;

  // Version 2 : données sous forme de liste de tableaux de tailles variées :)
  vector<int>* dummy_vector = new vector<int>();
  LogicalBoard* board0 = new LogicalBoard(0,0,dummy_vector); // id 0, 0 dimensions, tailles (vecteur vide car 0 dimensions)
  board0->setContent(dummy_vector,NBAL);
  this->plateaux = new  vector<LogicalBoard*>();
  this->plateaux->push_back(board0); 
  
  this->idJoueurCourant=0;
  this->playerList = new vector<Player*>();

  this->numTour = 0;
  this->rollback_stack = new vector<Coup*>();
}

void State::test(string s)
{
  if( ! this->playerList ) { die("playerlist-"+s+" fails!"); }
  if( ! (*this->playerList)[0] ) { die(s+"playerlist[0] fails!"); }
  if( ! (*this->playerList)[1] ) { die(s+"playerlist[1] fails!"); }
  if( ! this->getJoueurActif() ) { die(s+"getJoueurActif fails!"); }
  cout << "test playerlist-"+s+" ok!"<< endl;
}

// this constructor should call the default constructor thereabove and the create lc, the link to the lua script.
State::State(string luaConfFile){
  this->plateaux = new  vector<LogicalBoard*>();

  this->lc = new LuaCall(luaConfFile);
  //this-> plateaux = lc->getBoards() ? (à voir)

  // création d'un plateau par défaut en attendant mieux
  vector<int>* dummy_vector = new vector<int>();
  LogicalBoard* board0 = new LogicalBoard(0,0,dummy_vector); // id 0, 0 dimensions, tailles (vecteur vide car 0 dimensions)
  board0->setContent(dummy_vector,NBAL);
  this->plateaux->push_back(board0); 

  this->idJoueurCourant=0;
  this->playerList = new vector<Player*>(); 

  this->rollback_stack = new vector<Coup*>();

  cout << "TEST : "<< this->idJoueurCourant << endl;
}

// constructeur de copie
State::State(const State& etat)
{
  //this->nballumettes = etat.nballumettes;
  this->plateaux = new vector<LogicalBoard*>();
  this->lc = etat.lc;
  // copie chaque élément du tableau
  for(int i=0;i < (int)etat.plateaux->size();i++){
    this->plateaux->push_back( new LogicalBoard((*etat.plateaux)[i]));
  }

  this->idJoueurCourant=etat.idJoueurCourant;
  this->playerList = new vector<Player*>();

  this->numTour = etat.numTour;

  this->rollback_stack = new vector<Coup*>();
  for(int i=0;i < (int)etat.rollback_stack->size();i++){
    this->rollback_stack->push_back(new Coup( (*etat.rollback_stack)[i] ));
  }

}


// constructeur permettant de générer l'état suivant à partir de l'état initial et du coup joué.
/*State::State(State etatInitial, Coup coupJoue)
{
  this->plateaux = new vector<LogicalBoard*>();

  //  State etatTmp = etatInitial; // copie?
  for(int i=0; i<(int)coupJoue.actionList->size(); i++){
    Action* pa = (*coupJoue.actionList)[i];
    pa->execute_mod(this);
  }

  // if(etatTmp.nballumettes <0 ){ die("c'est pas bien tricheur"); }
  if((*this->plateaux)[0]->getContent(new vector<int>()) < 0 ){ die("c'est pas bien tricheur"); }

  //  this->playerList = new vector<Player*>();   // utile?

  this->clone(etatTmp); // permet d'instancier les valeurs de l'object en cours de construction
  this->joueurSuivant(); 

  //this->idJoueurCourant=etat.idJoueurCourant;

  }*/

  // la meme mais on n'instancie pas de nouvel état (il faudra stocker les infos dans une pile de facon à pouvoir revenir à l'état précédent.
void State::update(Coup coupJoue)
{
  Coup* pcoup_inverse = new Coup();
  for(int i=0; i<(int)coupJoue.actionList->size(); i++){
    Action* pa = (*coupJoue.actionList)[i];
    pa->execute_mod(this);

    Action* pa_inverse = pa->getInverse();
    pcoup_inverse->addActionFirst(pa_inverse);
  }

  rollback_stack->push_back(pcoup_inverse);

  // if(etatTmp.nballumettes <0 ){ die("c'est pas bien tricheur"); }
  if((*(this->plateaux))[0]->getContent(new vector<int>()) < 0 ){ die("c'est pas bien tricheur"); }

  joueurSuivant();
}

void State::rollback()
{
  Coup* anticoup = (*rollback_stack)[rollback_stack->size()-1];
   
  for(int i=0; i<(int)anticoup->actionList->size(); i++){
    Action* pa = (*anticoup->actionList)[i];
    pa->execute_mod(this);
  }

  rollback_stack->pop_back(); // this destroys the removed element.
}

void State::createIAPlayer(string nom){
  int nvId = this->playerList->size();
  Player* pp = (Player*)new IA(nom,nvId);
  this->playerList->push_back(pp);  
}
void State::createHumanPlayer(string nom){
  int nvId = this->playerList->size();
  Player* pp = (Player*)new HumanPlayer(nom,nvId);
  this->playerList->push_back(pp); 
}


/*
vector<LogicalBoard> State::getBoardList(){
  die("tu me cherches, là!");
}

vector<Piece> State::getPieceList(){
  die("connard!");
}
*/

/* the previous version

vector<Coup*> State::getCoupsPossibles(){
  vector<Coup*> res;
  int nballumettes = (*this->plateaux)[0]->getContent(new vector<int>());
  cout << " | State::getCoupsPossibles("<< nballumettes <<")"<<endl;
  for(int i = 1; (i <= nballumettes) && i<=3; i++ ){
    Coup* c = new Coup(i);
    cout << " | `-> " << c->toString() <<endl;
    res.push_back(c);
  }
  return res;
  }*/



vector<Coup*> State::getCoupsPossibles()
{

  int nballumettes = (*this->plateaux)[0]->getContent(new vector<int>());
 
  vector<Coup*> coups = lc->coupvector_call("CoupsPossibles",nballumettes);

  return coups;
}


bool State::partieNulle(){
  return false;
}
  // si un des joueurs est gagnant dans la position actuelle, renvoie un pointeur vers l'heure gagnant. Sinon renvoie null (ex : aux echecs, il a bloqué l'adversaire et il met son roi en echec)
// 
// lorsque cette fonction est appelée, le joueur actif est déjà placé au joureur suivant.
// Si ce joueur n'a plus d'alumettes a prendre, alors, il a gagné, car cela veut dire que son adversaire a pris la dernière.
int State::getIdGagnant()
{
  //TODO : transformer Player* getGagnant en int getIdGagnant ?
  int nballumettes = (*this->plateaux)[0]->getContent(new vector<int>());
  if(nballumettes == 0){  
    return this->idJoueurCourant;
  }

  return -1; 
}
int State::getNumTour(){
  return this->numTour;
}
Player* State::getGagnant()
{
  int idGagnant = this->getIdGagnant(); 

  if( idGagnant < 0) return (Player*)0;
  else
    {       
      return (*this->playerList)[idGagnant];
    }
}

Player* State::getJoueurActif(){
  return (*this->playerList)[this->idJoueurCourant];
  //  return this->p_joueur;
}
int State::getIdJoueurActif(){
  return this->idJoueurCourant;
}

Player* State::getJoueurActifSuivant(){ 
  die("deprecated2");
  return (*this->playerList)[(this->idJoueurCourant + 1) % NBJOUEURS ];
}
//void State::setIdJoueurActif(int id_player){
// die("depreacted : use State->joueurSuivant() instead");
//  this->idJoueurCourant = id_player;
//}
void State::joueurSuivant(){ 
  this->idJoueurCourant=(this->idJoueurCourant+1) % NBJOUEURS;
  if(this->idJoueurCourant==0){
    this->numTour++;
  }
}

// clone : affecte toutes les valeurs de l'objet s à l'objet this;
void State::clone(State s)
{
  this->idJoueurCourant = s.idJoueurCourant;
  this->lc = s.lc;

  //this->nballumettes = s.nballumettes;
  this->plateaux = new vector<LogicalBoard*>(1);
  (*this->plateaux)[0] = new LogicalBoard( (*s.plateaux)[0]);
  //  (*this->plateaux)[0]->setContent(new vector<int>(), (*s.plateaux)[0]->getContent(new vector<int>()));
       
  this->playerList = s.playerList;
  //{
  //  this->playerList->push_back((*s.playerList)[i]);
  //}

  this->numTour = s.numTour;
}


int State::getNbAllumettes(){
  return (*this->plateaux)[0]->getContent(new vector<int>());
  //  return this->nballumettes;
}
void State::setNbAllumettes(int i){
  //this->nballumettes=i;
  (*this->plateaux)[0]->setContent(new vector<int>(),i);
}
long State::evaluerEtat(int id_player){
// si la fonction lua estdéfinie fo pas hésiter
// sinon on voulait mettre en place une fonction générique...
  return 0; // il n'y a pas d'avantage particulier a avoir beaucoup d'allumettes => aucune heuristique particulière, faut juste éviter de perdre.
// on sait qu'il faut laisse à son adversaire 1, 5, 9, 11... etc allumettes, mais c'est justement le but du test de vérifier que le minmax reproduit bien ce comportement.
}
string State::toString()
{
  string res="";
  for(  unsigned int numplateau = 0; numplateau < this->plateaux->size(); numplateau++ )
  {
    LogicalBoard plateau =  (*this->plateaux)[0];
    res = res + "P" + (numplateau<10 ? " " : "") + my_int_to_string(numplateau) + " " + plateau.toString();

  }
  return res;
}

