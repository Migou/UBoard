#include "Player.hh"

//int idjoueur(Player* p_p){
//  die("fonction idjoueur deprecated");
//  return p_p->getId();
//}

Player::Player(string nom,int id)
{
  this->nom = nom;
  this->id = id;
}

string Player::toString()
{
  return my_int_to_string(this->id) + "_" + this->nom;
}
