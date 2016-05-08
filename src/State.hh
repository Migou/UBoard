#ifndef __VB_STATE_
#define __VB_STATE_

#include "constants.hh"
#include "LogicalBoard.hh"
#include "LuaCall.hh"
#include <vector>
#include <string>
#include "Player.hh"
#include "Coup.hh"
#include "utils.hh"
using namespace std;





// pre : les ids des joueurs sont unmériques : 0, 1, ... et correspond à leur placement dans le tableau playerList
class State
{
private :
  //vector<LogicalBoard> logicalBoardList;
  //vector<Piece> piecesList;
  //int nballumettes; // pour le test
  vector<LogicalBoard*>* plateaux;
  // Player* p_joueur;  // le joueur en cours : à remplacer par le numero d'ordre du joueur
  vector<Player*>* playerList;
  LuaCall* lc;
  int idJoueurCourant; // le joueur dont c'est le tour. Son numero d'ordre dans le tableaprécédent
  int numTour;
  vector<Coup*>* rollback_stack; // liste des coups à défaire lors de l'exploration de l'arbre des coups possibles
  // a ne pas confondre avec undo_stack, si l'on veut pouvoir tenir l'historique des coups joués.

public:
  State();
  State(string s);
  State(const State& e); 
  //  State(State e,Coup c);

  void clone(State s); // copie les attributs de s dans l'état this.
  void createIAPlayer(string); // ajouter un joueur d'id différent des précédents et portant le nom n
  void createHumanPlayer(string); // ajouter un joueur d'id différent des précédents et portant le nom n
  void test(string s);  
  // la meme mais on n'instancie pas de nouvel état (il faudra stocker les infos dans une pile de facon à pouvoir revenir à l'état précédent.
  void update(Coup);
  void rollback();
  //  vector<LogicalBoard> State::getBoardList();
  // vector<Piece> State::getPieceList();
  vector<Coup*> getCoupsPossibles();
  long evaluerEtat(int id_player);
  bool partieNulle();
  // si un des joueurs est gagnant dans la position actuelle, renvoie un pointeur vers l'heure gagnant. Sinon renvoie null (ex : aux echecs, il a bloqué l'adversaire et il met son roi en echec)
  int getNumTour();
  Player* getGagnant();
  int getIdGagnant();
  Player* getJoueurActif();
  int getIdJoueurActif();
  Player* getJoueurActifSuivant(); // utile pour générer l'état du tour suivant
  void setJoueurActif(Player*);
  void joueurSuivant(); // incremente le idJoueurCourant et numTour
  //  State getNewState4nectTurn(); // TODO : à ajouter à l'architecture? crée un état vierge avec juste le joueur actif suivant
  int getNbAllumettes();
  void setNbAllumettes(int i);

};

#else
class State;

#endif
