#ifndef _vb_logicalboard_
#define _vb_logicalboard_

#include "typeDonnees.hh"
#include "Grid.hh"
#include <vector>
using namespace std;

typedef struct _dimensionInfo {
  int range; //from 0 to range-1
  int loops; // bord (gauche) collé au bord droit
  int direction; // la direction vers laquelle on se dirige lorsqu'on parcourt la dimension par indices croissants N(0) S(1) W(2) E(3) Down(4) Up(5) ou une dimension ad hoc pour les cas de plateaux zarbis.
  int reverseDirection; // utile? la direction vers laquelle on se dirige lorsqu'on parcourt la dimension par indices décroissants 
  //  int mirror;
  // int moebius;
  // int reverse loop;
} dimensionInfo;

class LogicalBoard {
 private:
  int boardId;
  int nbDimensions;
  vector<struct _dimensionInfo>* dimensionsInfo;
  Grid* datagrid;
 public:
  LogicalBoard(int boardId,int nbDimensions,vector<int>* tailles); // crée un plateau basique genre echecs
  LogicalBoard(int boardId,int nbDimensions,vector<struct _dimensionInfo>* dimensionsInfo); // crée un plateau avec possibilités de formes spéciales
  LogicalBoard(LogicalBoard* lb); // constructeur de copie
  int getNbDimensions();
  struct _dimensionInfo getDimensionInfo(int numDimension);
  typedonnees getContent(vector<int>* coordonnees);
  void setContent(vector<int>* coordonnees,typedonnees valeur);
};

#else
class LogicalBoard;
#endif

