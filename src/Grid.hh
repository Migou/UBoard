#ifndef _vb_grid_
#define _vb_grid_

#include "typeDonnees.hh"
#include "utils.hh"
#include <vector>
using namespace std;

// la classe Grid et ses héritières sert à gérer facilement des tableaux à n dimensions n allant de 0 à ... au moins 2.
// la classe Grid ne devrait pas être visible en dehors de la classe LogicalBoard dont elle est une partie intégrante
// utilisez les accesseurs de la classe logical board pour parvenir à vos fins.
class Grid
{
public:
  virtual void set(vector<int>*,typedonnees valeur)=0;
  virtual typedonnees get(vector<int>*)=0;
  virtual Grid* getClone()=0;
};

class Grid0D : Grid
{
private:
  typedonnees donnee;
public:
  void set(vector<int>*,typedonnees valeur);
  typedonnees get(vector<int>*);
  Grid* getClone();
};

class Grid1D : Grid
{
private:
  vector<typedonnees> donnees;
public:
  void set(vector<int>*,typedonnees valeur);
  typedonnees get(vector<int>*);
  Grid* getClone();
};

class Grid2D : Grid
{
private:
  vector<vector<typedonnees> > donnees;
public:
  void set(vector<int>*,typedonnees valeur);
  typedonnees get(vector<int>*);
  Grid* getClone();
};

#else
    class Grid;
    class Grid0D;
    class Grid1D;
    class Grid2D;
#endif
