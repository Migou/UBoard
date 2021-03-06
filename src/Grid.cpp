#include "Grid.hh"
#include "utils.hh" // my_int_to_stringusing namespace std;


void Grid0D::set(vector<int>* coords,typedonnees valeur){
  if(coords->size() != 0){ die("dimension incorrecte, 1 attendu"); }
  this->donnee = valeur;
}

typedonnees Grid0D::get(vector<int>* coords)
{
  if(coords->size() != 0){ die("dimension incorrecte, 1 attendu"); }
  return this->donnee;
}

Grid* Grid0D::getClone(){
  Grid0D* clone = new Grid0D();
  vector<int>* dummy = new vector<int>();
  clone->set(dummy,this->get(dummy));
  return clone;
}

string Grid0D::toString()
{
  return "0D grid="+ my_int_to_string(this->donnee);
} 


void Grid1D::set(vector<int>* coords,typedonnees valeur)
{
  if(coords->size() != 1){ die("dimension incorrecte, 1 attendu"); }
  this->donnees[(*coords)[0]] = valeur;
}

typedonnees Grid1D::get(vector<int>* coords)
{
  if(coords->size() != 1){ die("dimension incorrecte, 1 attendu"); }
  return this->donnees[(*coords)[0]];
}

Grid* Grid1D::getClone(){
  Grid1D* clone = new Grid1D();

  for(int i = 0; i < (int)this->donnees.size(); i++)
  {
    clone->donnees.push_back(this->donnees[i]); //!\\ attention, si la donnée elle meme est un objet, il faudra appeler une méthode de clonage... on n'en sort pas....
  }

  return clone;
}

string Grid1D::toString()
{
  string res =  "[";
  for(int i = 0; i < (int)this->donnees.size(); i++)
  {
    res = res + my_int_to_string(this->donnees[i]) + " ";
  }
  return res + "]";
} 


void Grid2D::set(vector<int>* coords,typedonnees valeur){
  if(coords->size() != 2){ die("dimension incorrecte, 1 attendu"); }
  this->donnees[(*coords)[0]][(*coords)[1]] = valeur;
}

typedonnees Grid2D::get(vector<int>* coords){
  if(coords->size() != 2){ die("dimension incorrecte, 1 attendu"); }
  return this->donnees[(*coords)[0]][(*coords)[1]];
}


Grid* Grid2D::getClone(){
  Grid2D* clone = new Grid2D();

  for(int i = 0; i < (int)this->donnees.size(); i++)
    {
      vector<typedonnees>* tmp = new vector<typedonnees>();
      for(int j = 0; i < (int)this->donnees[i].size(); j++)
	{
	  tmp->push_back(this->donnees[i][j]); //!\\ attention, si la donnée elle meme est un objet, il faudra appeler une méthode de clonage... on n'en sort pas....
	}
      clone->donnees.push_back(*tmp);
    }

  return clone;
}

string Grid2D::toString()
{
  string res =  "[";

  for(int i = 0; i < (int)this->donnees.size(); i++)
    {
      for(int j = 0; i < (int)this->donnees[i].size(); j++)
	{
	  res = res + my_int_to_string(this->donnees[i][j]) + " ";
	}
      res = res + "]\n";
      
    }
  return res ;
} 
