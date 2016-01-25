
/**************
 * fichier bouchon pourtester la classe IA
 *
 * reproduit le jeu des allumettes
 * celui qui prend la dernière allumette a perdu.
 */

#include "constants.hh"
#include <iostream>
#include <vector>
#include <stdlib.h> 
#include "utils.hh"
#include "State.hh"
#include "Player.hh"
#include "Coup.hh"

using namespace std;

int main()
{
  State etat;  
  etat.createIAPlayer("IA-Hvé");
  etat.createHumanPlayer("Xavier");

   while(! etat.getGagnant() && ! etat.partieNulle() )
   {
     cout << "*************\n* Tour n° "<<etat.getNumTour()<<" *\n*"<<etat.getJoueurActif()->toString()<<" *\n*************"<<endl;

     Player* joueurCourant = etat.getJoueurActif();
     Coup c = joueurCourant->getCoup(etat);
     
     cout << "joueur " <<  etat.getJoueurActif()->toString() << " PREND " << c.toString() << " ALLUMETTES"<<endl;

      State etat2(etat,c);
      etat.clone(etat2);

      cout << "   ... il reste " << etat.getNbAllumettes() << " allumettes"<<endl;
   }

   Player* gagnant = etat.getGagnant();
   cout << "Le gagnant est : "<< gagnant->toString() << endl;
   if(gagnant->estHumain() > 0)
   {
     cout << "Félicitations "<< gagnant->getName() <<"!"<< endl;
   }

 return 1;
}
