
/**************
 * fichier bouchon pourtester la classe IA
 *
 * reproduit le jeu des allumettes
 * celui qui prend la dernière allumette a perdu.
 */

#include <iostream>
#include <vector>
#include <stdlib.h> 
#include "utils.h"
#include "ia_utest.h"
#include "ia.h"
using namespace std;

  
// constructeur permettant de charge l'état initial à partir d'un fichier de conf lua
State::State(){
  this->nballumettes = 10;
  this->p_joueur= (Player*)0;
}
State::State(string luaConfFile){
  die("con");
}

  // constructeur permettant de générer l'état suivant à partir de l'état initial et du coup joué.
State::State(State etatInitial, Coup coupJoue)
{
  this->nballumettes = etatInitial.nballumettes - coupJoue;
  this->p_joueur = (Player*)0; // better segfault than bug

  if(this->nballumettes <0 ){ die("c'est pas bien tricheur"); }
if(this->nballumettes == 0 ){ cout << "joueur "<< (int)*this->p_joueur << " va perdre :)" << endl; }
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
vector<Coup> State::getCoupsPossibles(){
  vector<Coup> res;
  for(int i = 1; i <= this->nballumettes; i++ ){
    res.push_back(i);
  }
  return res;
}


bool State::partieNulle(){
  return false;
}
  // si un des joueurs est gagnant dans la position actuelle, renvoie un pointeur vers l'heure gagnant. Sinon renvoie null (ex : aux echecs, il a bloqué l'adversaire et il met son roi en echec)
Player* State::getGagnant()
{
Player* pi = (Player*)malloc(sizeof(Player));
  if(this->nballumettes == 0){
  *pi = (((int)*p_joueur)-1)%2; // le joueur précédent a pris la dernière allumette, le con, ce dernier a donc perdu. 
    return pi;
  }
}

Player* State::getJoueurActif(){
  return this->p_joueur;
}
void State::setJoueurActif(Player* p){
  this->p_joueur = p;
}
int State::getNbAllumettes(){
return this->nballumettes;
}
long State::evaluerEtat(Player p){
// si la fonction lua estdéfinie fo pas hésiter
// sinon on voulait mettre en place une fonction générique...
  return 0; // il n'y a pas d'avantage particulier a avoir beaucoup d'allumettes => aucune heuristique particulière, faut juste éviter de perdre.
// on sait qu'il faut laisse à son adversaire 1, 5, 9, 11... etc allumettes, mais c'est justement le but du test de vérifier que le minmax reproduit bien ce comportement.
}




int main()
{
  State etat;
  Player p1 = (Player)0;
  Player p2 = (Player)1;

   while(! etat.getGagnant() && ! etat.partieNulle() )
   {
      Coup c = getCoup(etat);
      cout << "joueur " << (int)(*etat.getJoueurActif()) << " prend " << c << " allumettes"<<endl;

      // nouvel état, avec le joueur suivant
      etat = State(etat,c);
cout << "joueur " << (int)*etat.getJoueurActif() << " prend " << c << " allumettes"<<endl;

      etat.setJoueurActif( *etat.getJoueurActif() == p1 ? &p2 : &p1 );
      cout << "   ... il reste " << etat.getNbAllumettes() << " allumettes";
   }

cout << "Le gagnant est : "<< *(etat.getGagnant()) << endl;
}


