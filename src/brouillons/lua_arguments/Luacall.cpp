#include "Luacall.hpp"
#include <stdlib.h>
#include <string.h> // pour la fonction strlen
#include <stdarg.h> // pour les fonctions à nb d'arguments variables

Luacall::Luacall(string luafilename)
{
  lua_state=luaL_newstate();
  luaL_openlibs(lua_state);
  if(luaL_dofile(lua_state,luafilename.c_str())==1)
  {
    cout << "erreur à l'ouverture du fichier de script lua : '" <<luafilename<<"'"<<endl;  
    exit(1);
  }
}

// fonction sans argument
int Luacall::int_call(string func)
{
  string argtypes="";
  return generic_int_call(func,argtypes.c_str());
}

// fonction à 1 argument int
int Luacall::int_call(string func,int a1)
{
  string argtypes="i";
  return generic_int_call(func,argtypes.c_str(),a1);
}

// fonction à 1 argument string
int Luacall::int_call(string func,string a1)
{
  string argtypes="s";
  return generic_int_call(func,argtypes.c_str(),a1.c_str());
}

// argtypes string composée de "s" et de "i" par exemple pour string et int. cela donne donc "iisi" pour 4 arguments...
int Luacall::generic_int_call(string func,const char* argtypes,...)
{
  int nbargs=0;
  va_list varg;

  lua_getglobal(lua_state, func.c_str());

  //push des arguments

  va_start(varg, argtypes); // initialisation de la liste des arguments
  // apparemment, va_start se base sur le dernier argument fice pour trouver les arguments suviants
  for(int i = 0; i < strlen(argtypes); i++)
  {
    nbargs++;
    if( *argtypes == 's')
    {
      char* arg = va_arg(varg, char*);
      cout << "get string arg=" << arg <<endl;
      lua_pushstring(lua_state,arg); 
    }
    else if(*argtypes == 'i')
    {      
      int arg = va_arg(varg,int);
      cout << "get int arg=" << arg <<endl;
      lua_pushnumber(lua_state, arg);
    }
    else
    {
	cout << "error in argtype strings : expected types should be either 's' or 'i'" << endl;
	exit(2);
    }
    va_end(varg);
    argtypes++; // on va une case plus loin sur la string )))
  }


  if( lua_pcall(lua_state, nbargs, 1, 0) != 0)
  {
    cout << "impossible de lancer la fonction \"" << func << "\" : " << lua_tostring(lua_state, -1) <<endl;
    exit(1);
  }
  if (!lua_isnumber(lua_state, -1))
  {
    cout << "function `"<< func <<"' must return a number" << endl;
    exit(3);
  }
  int retour = lua_tonumber(lua_state, -1);
  lua_pop(lua_state, 1);  
  return retour;
}


string Luacall::generic_string_call(string func,const char* argtypes, ...)
{
  int nbargs=0;
  va_list varg;

  lua_getglobal(lua_state, func.c_str());

  //push des arguments

  va_start(varg, argtypes); // initialisation de la liste des arguments
  // apparemment, va_start se base sur le dernier argument fice pour trouver les arguments suviants
  for(int i = 0; i < strlen(argtypes); i++)
  {
    nbargs++;
    if( *argtypes == 's')
    {
      char* arg = va_arg(varg, char*);
      cout << "get string arg=" << arg <<endl;
      lua_pushstring(lua_state,arg); 
    }
    else if(*argtypes == 'i')
    {      
      int arg = va_arg(varg,int);
      cout << "get int arg=" << arg <<endl;
      lua_pushnumber(lua_state, arg);
    }
    else
    {
	cout << "error in argtype strings : expected types should be either 's' or 'i'" << endl;
	exit(2);
    }
    va_end(varg);
    argtypes++; // on va une case plus loin sur la string )))
  }


  if( lua_pcall(lua_state, nbargs, 1, 0) != 0)
  {
    cout << "impossible de lancer la fonction \"" << func << "\" : " << lua_tostring(lua_state, -1) <<endl;
    exit(1);
  }
  if (!lua_isstring(lua_state, -1))
  {
    cout << "function `"<< func <<"' must return a string" << endl;
    exit(3);
  }
  char* retour = lua_tostring(lua_state, -1);
  lua_pop(lua_state, 1);  
  string retour2 = new string(retour);
  return retour2;

}

string Luacall::string_call(string func)
{
  string argtypes="";
  return generic_string_call(func,argtypes.c_str());
}
