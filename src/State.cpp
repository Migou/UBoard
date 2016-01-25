#include "State.hh"
#include "IA.hh"
#include "Player.hh"
#include "HumanPlayer.hh"
#include "constants.hh"

// constructeur permettant de charge l'état initial à partir d'un fichier de conf lua
// post : le programmeur devra penser à ajouter des joueurs grâce à State::createPlayer
State::State(){
  // Version 1 : données représentées par un simple entier
  // this->nballumettes = NBAL;

  // Version 2 : données sous forme de lsite de tableaux de tailles variées :)
  vector<int>* dummy_vector = new vector<int>();
  LogicalBoard* board0 = new LogicalBoard(0,0,dummy_vector); // id 0, 0 dimensions, tailles (vecteur vide car 0 dimensions)
  board0->setContent(dummy_vector,NBAL);
  this->plateaux = new  vector<LogicalBoard*>();
  this->plateaux->push_back(board0); 
  
  this->idJoueurCourant=0;
  this->numTour = 0;
}

State::State(string luaConfFile){
  die("con");
}

// constructeur de copie
State::State(const State& etat)
{
  //this->nballumettes = etat.nballumettes;
  this->plateaux = new vector<LogicalBoard*>();
  // copie chaque élément du tableau
  for(int i=0;i < (int)etat.plateaux->size();i++){
    this->plateaux->push_back( new LogicalBoard((*etat.plateaux)[i]));
  }

  this->idJoueurCourant=etat.idJoueurCourant;
  this->numTour = etat.numTour;
}

  // constructeur permettant de générer l'état suivant à partir de l'état initial et du coup joué.
State::State(State etatInitial, Coup coupJoue)
{
  State etatTmp = etatInitial; // copie?
  for(int i=0; i<(int)coupJoue.actionList->size(); i++){
    
    Action* pa = (*coupJoue.actionList)[i];
    etatTmp = pa->execute(etatTmp);
  }

  // if(etatTmp.nballumettes <0 ){ die("c'est pas bien tricheur"); }
  if((*etatTmp.plateaux)[0]->getContent(new vector<int>()) < 0 ){ die("c'est pas bien tricheur"); }
  
  this->clone(etatTmp); // permet d'instancier les valeurs de l'object en cours de construction
  this->joueurSuivant(); 
}

void State::createIAPlayer(string nom){
  int nvId = this->playerList.size();
  Player* pp = (Player*)new IA(nom,nvId);
  this->playerList.push_back(pp);  
}
void State::createHumanPlayer(string nom){
  int nvId = this->playerList.size();
  Player* pp = (Player*)new HumanPlayer(nom,nvId);
  this->playerList.push_back(pp); 
}

  // la meme mais on n'instancie pas de nouvel état (il faudra stocker les infos dans une pile de facon à pouvoir revenir à l'état précédent.
void State::update(Coup coupJoue)
{
  die("plouf");
}

void State::rollBackCoup()
{
  die("bigre!");
}

/*
vector<LogicalBoard> State::getBoardList(){
  die("tu me cherches, là!");
}

vector<Piece> State::getPieceList(){
  die("connard!");
}
*/
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
      return this->playerList[idGagnant];
    }
}

Player* State::getJoueurActif(){
  return this->playerList[this->idJoueurCourant];
  //  return this->p_joueur;
}
int State::getIdJoueurActif(){
  return this->idJoueurCourant;
}

Player* State::getJoueurActifSuivant(){ 
  die("deprecated2");
  return this->playerList[(this->idJoueurCourant + 1) % NBJOUEURS ];
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

  //this->nballumettes = s.nballumettes;
  this->plateaux = new vector<LogicalBoard*>(1);
  (*this->plateaux)[0] = new LogicalBoard( (*s.plateaux)[0]);
  //  (*this->plateaux)[0]->setContent(new vector<int>(), (*s.plateaux)[0]->getContent(new vector<int>()));
       

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
