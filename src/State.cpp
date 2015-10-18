à mettre dans State.h
class State
{
private :
  vector<LogicalBoard> logicalBoardList;
  vector<Piece> piecesList;
Public :

}

---8<---
debut de state.cpp

// constructeur permettant de charge l'état initial à partir d'un fichier de conf lua
State::State(string luaConfFile){
  !!!
    }

  // constructeur permettant de générer l'état suivant à partir de l'état initial et du coup joué.
State::State(Coup coupJoue)
{
  !!!
    }

  // la meme mais on n'instancie pas de nouvel état (il faudra stocker les infos dans une pile de facon à pouvoir revenir à l'état précédent.
void State::update(Coup coupJoue)
{
  !!!
    }
void State::rollBackCoup()
{
  !!!
    }

vector<LogicalBoard> State::getBoardList(){
  !!!
    }

vector<Piece> State::getPieceList(){
  !!!
    }

vector<Coup> State::getCoupsPossibles(){
    !!!
      }

  // si un des joueurs est gagnant dans la position actuelle, renvoie un pointeur vers l'heure gagnant. Sinon renvoie null (ex : aux echecs, il a bloqué l'adversaire et il met son roi en echec)
Player* State::getGagnant()
{
  return 0;!!!
	     }

  



