#include <stdlib.h> //exit
#include <iostream>
#include <vector>
#include "IA.hh"
#include "utils.hh"
using namespace std;

// pas sur que ca soit précisément les bonnes valeusr mais pas loin.
#define MAXLONG 9223372036854775807 
#define MINLONG -9223372036854775806
#define INFINITY MAXLONG
#define MINUSINFINITY MINLONG
#define MAXPROF 64
#define RETOURMEILLEURCOUP if(prof==0){ (*p_meilleur_coup) = listeCoupsPossibles[meilleur_i]; }

long min(long a, long b){ return a<b ? a : b; }
long max(long a, long b){ return a>b ? a : b; }



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

  cout<< prefix << "alphaBeta(prof="<< prof <<"):" <<endl;

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
      int nbcoups = listeCoupsPossibles.size();
      for (int i =0; i<nbcoups; i++ )
      {
	Coup* pc = listeCoupsPossibles[i];
	cout << prefix << "TEST du coup n°" << i << " (" << pc->toString() <<")"<<endl;
	State Pi(*P,*pc); // c'est la version 1, où on instancie un nouvel état à chaque fois, parce que c'est la version prototype, mais après il vaudrait mieux exécuter le coup avant l'apper de fonction et le défaire à la sortie
	//version 2 : P->update(c);
        //Val = ALPHA-BETA(Pi, A, Min(B,Beta de P))
	long val = alpha_beta(&Pi,A,min(B,Beta),!est_min,id_joueur,prof+1,(Coup*)0); // le cast c'est juste pour se rapperkle ce que c'est que cet argument;
    
	//version 2 : P->rollbackCoup(c);
	  
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
      int nbcoups = listeCoupsPossibles.size();
      for (int i =0; i<nbcoups; i++ )
      {
	Coup* pc = listeCoupsPossibles[i];
	cout << prefix << "TEST du coup n°" << i << " (" << pc->toString() <<")"<<endl;
	State Pi(*P,*pc); // c'est la version 1, où on instancie un nouvel état à chaque fois, parce que c'est la version prototype, mais après il vaudrait mieux exécuter le coup avant l'apper de fonction et le défaire à la sortie
	//version 2 : P->update(c);
	//Val = ALPHA-BETA(Pi, Max(A,Alpha de P), B)
	long val = alpha_beta(&Pi,max(A,Alpha),B,!est_min,id_joueur,prof+1,(Coup*)0);
	//version 2 : P->rollbackCoup(c);

	if(val  > meilleur_val ){ meilleur_i = i; meilleur_val = val; }
 
        Alpha = max(Alpha, val);
	//Si Alpha de P >= B /*ceci est la coupure beta */
	if(Alpha >= B)
	{
	  //alors retourner Alpha de P
	  if(prof==0){ *p_meilleur_coup = *(listeCoupsPossibles[meilleur_i]); } //RETOURMEILLEURCOUP par copie

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


Coup IA::getCoup(State state)
{
  Coup* p_coup = new Coup() ; // coucou :-D
  cout << " getCoup, debut alpha-beta" << endl;

  // soit on lance à ce niveau et on s'arrange pour que alphabeta retourne le meilleur coup couple<long,Coup>
  alpha_beta(&state,MINUSINFINITY,INFINITY,0,state.getIdJoueurActif(),0,p_coup);

  cout<<  " getCoup, fin alpha-beta" <<endl;

  return *p_coup;
}
