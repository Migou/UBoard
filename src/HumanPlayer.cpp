#include "HumanPlayer.hh"
#include "Player.hh"
#include "State.hh"
#include <string>
#include <iostream>
using namespace std;

HumanPlayer::HumanPlayer(string n,int i) : Player(n,i)
{
}

int HumanPlayer::estHumain(){ return 1; }

Coup HumanPlayer::getCoup(State)
{
  cout << "Saisissez votre choix de coup 1-3 : ";
  int i_tmp;
  cin >> i_tmp;
  cout << "Vous avez saisi "<<i_tmp<<endl;
  Coup c(i_tmp);
  return c;
}

