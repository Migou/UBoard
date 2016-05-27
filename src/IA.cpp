#include <stdlib.h> //exit
#include <iostream>
#include <vector>
#include <climits>
#include "IA.hh"
#include "utils.hh"
using namespace std;

#define INFINITY LONG_MAX
#define MINUSINFINITY LONG_MIN
#define MAXPROF 64
#define RETOURMEILLEURCOUP if(prof==0){ (*p_meilleur_coup) = listeCoupsPossibles[meilleur_i]; }


long min(long a, long b){ return a<b ? a : b; }
long max(long a, long b){ return a>b ? a : b; }

void print_coups_possibles(vector<Coup*>* coups){
  cout << "(";
  for(unsigned int i=0; i< coups->size(); i++)
  {
    Coup* coup = (*coups)[i];
    cout << coup->toString() << " ";
  }
  cout<<")"<<endl;
}


// source : http://www.di.ens.fr/~granboul/enseignement/mmfai/algo2003-2004/tp5/
// est_min : indique si le but est de minimiser ou maximiser le score : normalement, lorsque c'est le tour du joueur on maximise, lorsque c'est le tour de l'adversaire, on minimise
// p_joueur => la personne pour qui on doit choisir le coup. Influence la notation du cas "feuille" = quand le jeu est fini
long alpha_beta(State* P,long A,long B,bool est_min,int id_joueur,int prof,Coup* p_meilleur_coup){
  int meilleur_i=0; // variables pour stocker le meilleur coup
  int meilleur_val; // idem.
  string prefix=" | ";
  int id_joueur_gagnant; 

  // prefixe
  for(int i=0; i<prof; i++){ prefix = prefix + ". "; }

  cout<< prefix << "alphaBeta(prof="<< prof <<"): " << P->toString() <<endl;

//fonction ALPHA-BETA(P, A, B) /* ici A est toujours inférieur à B */
  if(A > B){ die("erreur fatale : A doit être inférieur à B"); }

  //si P est une feuille alors retourner la valeur de P
  if(P->partieNulle()) return 0; // cas de feuille n°1 : partie Nulle
  if( (id_joueur_gagnant = P->getIdGagnant()) >= 0 ) // cas feuille n°2 : quelqu'un a gagné (-1 si pas de vainqueur)
  {
    if( id_joueur_gagnant == id_joueur ) return INFINITY; 
    return MINUSINFINITY; // c'est donc un des adversaires qui a gagné, pas bon du tout ca...
  }
  if(prof > MAXPROF) return P->evaluerEtat(id_joueur); // cas feuille n°3 partie non terminée, mais limitation de la profondeu d'exploration : évalue la situation du plateau du point de vue du joueur

  //sinon
  else
  {
    //initialiser Alpha de P à -infini et Beta de P à +infini
    long Alpha = MINUSINFINITY;
    long Beta = INFINITY;

    //si P est un noeud Min alors
    //  il s'agit du tour d'un adversaire.
    //  dans ce cas, Beta recoit le minimum des valeurs de alpha_beta(...), car l'adversaire sélectionnera le pire coup possible :)
    if(est_min)
    {
      //pour tout fils Pi de P faire
      vector<Coup*> listeCoupsPossibles = P->getCoupsPossibles();
      cout << prefix << "coups possibles = ";
      print_coups_possibles(&listeCoupsPossibles);
      int nbcoups = listeCoupsPossibles.size();
      if(nbcoups == 0){ die("cas non prévu : 0 coups possibles"); }

      for (int i =0; i<nbcoups; i++ )
      {
	Coup* pc = listeCoupsPossibles[i];
	cout << prefix << "TEST du coup n°" << i << " (" << pc->toString() <<")"<<endl;

	PRINTVECTPREFIX_toString(listeCoupsPossibles,"e");
	P->update(*pc); // on modifie l'état, il faudra penser à démodifier à la sotie du programme
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"f");

        //Val = ALPHA-BETA(Pi, A, Min(B,Beta de P))
	long val = alpha_beta(P,A,min(B,Beta),!est_min,id_joueur,prof+1,(Coup*)0); // le cast c'est juste pour se rapperkle ce que c'est que cet argument;
    	PRINTVECTPREFIX_toString(listeCoupsPossibles,"g");

	P->rollback(); // la mémorisation de ce qui doit être défait est à la charge de la classe état.
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"h");

	//Beta de P = Min(Beta de P, Val)
	Beta = min(Beta,val);

        //Si A >= Beta de P /*ceci est la coupure alpha */
	if(A >= Beta)
	{
	  //alors retourner Beta de P 
	  return Beta;
	}
      } //finfaire

      //retourner Beta de P
      return Beta;
    }
    else // sinon (NB : noeud max)
    {
      //pour tout fils Pi de P faire
      vector<Coup*> listeCoupsPossibles = P->getCoupsPossibles();
      cout << prefix << "coups possibles2 = ";
      print_coups_possibles(&listeCoupsPossibles);

      int nbcoups = listeCoupsPossibles.size();
      if(nbcoups == 0){ die("cas non prévu-2 : 0 coups possibles"); }

      for (int i =0; i<nbcoups; i++ )
      {
	Coup* pc = listeCoupsPossibles[i];
	cout << prefix << "TEST du coup n°" << i << " (" << pc->toString() <<")"<<endl;
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"a");
	P->update(*pc); 
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"b");
	//Val = ALPHA-BETA(Pi, Max(A,Alpha de P), B)
	long val = alpha_beta(P,max(A,Alpha),B,!est_min,id_joueur,prof+1,(Coup*)0);
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"c");
	P->rollback();
	PRINTVECTPREFIX_toString(listeCoupsPossibles,"d");

	if(val  > meilleur_val ){ meilleur_i = i; meilleur_val = val; }
 
        Alpha = max(Alpha, val);
	//Si Alpha de P >= B /*ceci est la coupure beta */
	if(Alpha >= B && prof > 0)
	{
	  //alors retourner Alpha de P
	  //if(prof==0){ *p_meilleur_coup = *(listeCoupsPossibles[meilleur_i]); } //RETOURMEILLEURCOUP par copie

	    return Alpha;
	}
      }//finfaire
      //retourner Alpha de P
      if(prof==0){ *p_meilleur_coup = *(listeCoupsPossibles[meilleur_i]); } //RETOURMEILLEURCOUP par copie
      return Alpha;
    }
  }
}


IA::IA(string n,int i) : Player(n,i)
{
}

int IA::estHumain(){ return 0; }


Coup IA::getCoup(State state)
{
  Coup* p_coup = new Coup() ; // coucou :-D
  cout << " getCoup, debut alpha-beta" << endl;

  // soit on lance à ce niveau et on s'arrange pour que alphabeta retourne le meilleur coup couple<long,Coup>
  alpha_beta(&state,MINUSINFINITY,INFINITY,0,state.getIdJoueurActif(),0,p_coup);

  cout<<  " getCoup, fin alpha-beta" <<endl;

  return *p_coup;
}
