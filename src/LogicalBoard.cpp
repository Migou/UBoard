#include "LogicalBoard.hh"
#include "utils.hh"
#include <stdlib.h> // test

LogicalBoard::LogicalBoard(LogicalBoard* lb) // constructeur de copie
{
  this->boardId = lb->boardId;
  this->nbDimensions = lb->nbDimensions;
  this->dimensionsInfo = new vector<struct _dimensionInfo>();
  for(int numDimension=0; numDimension<nbDimensions; numDimension++)
    {
      struct _dimensionInfo* copie = (struct _dimensionInfo*)malloc(sizeof(struct _dimensionInfo));
      *copie = (*lb->dimensionsInfo)[numDimension];
      this->dimensionsInfo->push_back(*copie);
    }

  this->datagrid = lb->datagrid->getClone();
  
}
LogicalBoard::LogicalBoard(int boardId,int nbDimensions,vector<int>* taille){
  this->boardId = boardId;
  this->nbDimensions = nbDimensions;
  struct _dimensionInfo basicdimensionInfo;
  basicdimensionInfo.loops = 0;
  for(int numDimension=0; numDimension<nbDimensions; numDimension++)
    {
      basicdimensionInfo.range = (*taille)[numDimension];
      basicdimensionInfo.direction = 2*numDimension +1;
      basicdimensionInfo.reverseDirection = 2*numDimension ;
      this->dimensionsInfo->push_back(basicdimensionInfo); // dimension1
    }

  

  switch ( nbDimensions )
    {
    case 0 :
      this->datagrid = (Grid*)new Grid0D();
      break;
    case 1 :
      this->datagrid = (Grid*)new Grid1D();
      break;
    case 2 :
      this->datagrid = (Grid*)new Grid2D();
      break;
    default  : 
      die("valeur non prévue");
    }
}
LogicalBoard::LogicalBoard(int boardId,int nbDimensions,vector<struct _dimensionInfo>* dimensionsInfo){

  this->boardId = boardId;
  this->nbDimensions = nbDimensions;
  this->dimensionsInfo = dimensionsInfo;
}

int LogicalBoard::getNbDimensions()
{
  return this->nbDimensions;
}
struct _dimensionInfo LogicalBoard::getDimensionInfo(int numDimension)
{
  if(numDimension<0 || numDimension > this->nbDimensions)
    {
      die("fatal error, numéro de dimension "+my_int_to_string(numDimension)+" n'est pas inclus dans [0, "+my_int_to_string(nbDimensions)+"[");
    }
  return (*dimensionsInfo)[numDimension];
}

int LogicalBoard::getContent(vector<int>* coordonnees){
  return this->datagrid->get(coordonnees); // :-) et c'est là qu'on apprécie la classe virtuelle Grid, qui permet d'homogénéiser le traitement!!!
}
void  LogicalBoard::setContent(vector<int>* coordonnees,typedonnees valeur){
  if(this->datagrid==0){ die("datagrid is null"); }
   this->datagrid->set(coordonnees,valeur); // :-) et c'est là qu'on apprécie la classe virtuelle Grid, qui permet d'homogénéiser le traitement!!!
}

