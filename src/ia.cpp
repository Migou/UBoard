// pas sur que ca soit précisément les bonnes valeusr mais pas loin.
#define MAXLONG 9223372036854775807 
#define MINLONG -9223372036854775806
#define INFINITY MAXLONG
#define MINUSINFINITY MINLONG
#define MAXPROF 13

long min(long a, long b){ return a<b ? a : b; }
long max(long a, long b){ return a>b ? a : b; }
void die(string mess){ 
  cerr << mess << endl;
  exit(1);
}

// source : http://www.di.ens.fr/~granboul/enseignement/mmfai/algo2003-2004/tp5/
// est_min : indique si le but est de minimiser ou maximiser le score : normalement, lorsque c'est le tour du joueur on maximise, lorsque c'est le tour de l'adversaire, on minimise
// p_joueur / p_attendeur => je me disais qu'on en aurait besoin pour déterminer qui gagne, mais on devrait pouvoir s'en sortir avec la seule information est_min... fo juste pas se planter.
long alpha_beta(State* P,long A,long B,est_min,p_joueur,p_attendeur,int max_prof){
//fonction ALPHA-BETA(P, A, B) /* ici A est toujours inférieur à B */
  if(A > B){ die("erreur fatale : A doit être inférieur à B"); }

  //si P est une feuille alors  
  if(max_prof<=0){
    return 
  }

  player* p_gagnant =  P->getGagnant(); /* cela peut se remplacer par : 
 if(est_min){ return MINUSINFINITY (ou INFINITY tout court?) faut pas se planter. 
 if(est_max){ return INFINITY (ou MINUSINFINITY tout court?) faut pas se planter. 
					   
					 */
  if(p_gagnant)
  {
    //retourner la valeur de P
    if( p_gagnant == p_joueur ){
      return INFINITY;
    }
    elsif( p_gagnant == p_attendeur )
    {
	return MINUSINFINITY;
    }
    else{
      die("fatal error, cas impossible");
    }
  }
  //sinon
  else
  {
    //initialiser Alpha de P à -infini et Beta de P à +infini
    long Alpha = MINUSINFINITY;
    long Beta = INFINITY;

    //si P est un noeud Min alors
    if(est_min)
    {
      //pour tout fils Pi de P faire
      vector<Coup> listeCoupsPossibles = P->getCoupsPossibles();
      int nbcoups = listeCoupsPossibles.size();
      for (int i =0; i<nbcoups; i++ )
      {
	Coup c = listeCoupsPossibles[i];
	State Pi = new State(c); // c'est la version 1, où on instancie un nouvel état à chaque fois, parce que c'est la version prototype, mais après il vaudrait mieux exécuter le coup avant l'apper de fonction et le défaire à la sortie
	//version 2 : P->update(c);
        //Val = ALPHA-BETA(Pi, A, Min(B,Beta de P))
	long val = alpha_beta(Pi,A,min(B,Beta),!est_min,p_attendeur,p_joueur); // inversion des deux joueurs à l'appel récursif.
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
      vector<Coup> listeCoupsPossibles = P->getCoupsPossibles();
      int nbcoups = listeCoupsPossibles.size();
      for (int i =0; i<nbcoups; i++ )
      {
	Coup c = listeCoupsPossibles[i];
	State Pi = new State(c); // c'est la version 1, où on instancie un nouvel état à chaque fois, parce que c'est la version prototype, mais après il vaudrait mieux exécuter le coup avant l'apper de fonction et le défaire à la sortie
	//version 2 : P->update(c);
	//Val = ALPHA-BETA(Pi, Max(A,Alpha de P), B)
	long val = alpha_beta(Pi,max(A,Alpha),B,!est_min,p_attendeur,p_joueur);
	//version 2 : P->rollbackCoup(c);
 
        Alpha = max(Alpha, Val)
	//Si Alpha de P >= B /*ceci est la coupure beta */
	if(Alpha >= B)
	{
	  //alors retourner Alpha de P
	  return Alpha
	}
      }//finfaire
      //retourner Alpha de P
      return Alpha;
    }
  }
}


Coup IA::getCoup(State state)
{
  // soit on lance à ce niveau et on s'arrange pour que alphabeta retourne le meilleur coup couple<long,Coup>
  alpha_beta(state,MINUSINFINITY,INFINITY,0,p_joueur,p_attendeur,MAXPROF){

  vector<Coup> listeCoupsPossibles = state->getCoupsPossibles();
  int nbcoups = listeCoupsPossibles.size();
  if(nbcoups <= 0){ die("il n'y a aucun coup possible dans l'état courrant du plateau")}

  for (int i =0; i<nbcoups; i++ )
  {
    long meilleure_val;
    int meilleur_i=0;
    Coup c = listeCoupsPossibles[i];
    State Pi = new State(c); 
    val = alpha_beta(Pi,MINUSINFINITY,INFINITY,1,p_attendeur,p_joueur,MAXPROF)
      if( val > meilleure_val){
	meilleure_val = val;
	meilleur_i = i;
      } 
  }

  return listeCoupsPossibles[i];
}
