#ifndef __ia_utest__
#define __ia_utest__
#include<iostream>
using namespace std;

typedef int Coup;
typedef int Player; //lol, je ne suis pas un numéro!

class State
{
private :
  //vector<LogicalBoard> logicalBoardList;
  //vector<Piece> piecesList;
  int nballumettes; // pour le test
  Player* p_joueur;  // pour le test?
public :
  State();
  State(string);
  State(State,Coup);
  
  // la meme mais on n'instancie pas de nouvel état (il faudra stocker les infos dans une pile de facon à pouvoir revenir à l'état précédent.
  void update(Coup);
  void rollBackCoup();
  //  vector<LogicalBoard> State::getBoardList();
  // vector<Piece> State::getPieceList();
  vector<Coup> getCoupsPossibles();
  long evaluerEtat(Player);
  bool partieNulle();
  // si un des joueurs est gagnant dans la position actuelle, renvoie un pointeur vers l'heure gagnant. Sinon renvoie null (ex : aux echecs, il a bloqué l'adversaire et il met son roi en echec)
  Player* getGagnant();
  Player* getJoueurActif();
  void setJoueurActif(Player*);
  int getNbAllumettes();
};

#endif
