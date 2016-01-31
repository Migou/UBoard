#include "Luacall.hh"
#include <stdlib.h>
#include <string.h> // pour la fonction strlen
#include <stdarg.h> // pour les fonctions à nb d'arguments variables

#include <string>
using namespace std;

/* use these so as to avoid to create a const string at each call time.
const char* STR_SI = c_str("si");
const char* STR_VOID = c_str("");
const char* STR_S = c_str("s");
const char* STR_I = c_str("i");
const char* STR_IS = c_str("is");
*/

void Luacall::make_callable_from_lua(string functionName, int  (*functionPointer)(lua_State*) )
{
  cout << "making function "<< functionName<<" callable from lua."<<endl;
  lua_pushcfunction(this->lua_state, functionPointer);
  lua_setglobal(lua_state, functionName.c_str());
}

/*********************************    
the first parameter describes the type of further arguments :
 - s : char* (NB : not string, as strings are not "trivially-copyable")
 - i : int
 - to be continued...

usage : 
  return to_lua("si",mystring,myint);

Some explainations for curious people.

In lua, functions can expect several return values
  e.g. : a, b = min_max(5, 2, 10, 3)
Note that returning values to lua should be done the following way :
  lua_pushnumber(l, 12);  // pushing the first return value [to lua's function call stack]
  lua_pushstring(l, "See you space cowboy"); //pushing the second return value
  return 2;  // number of return values
******************************/
int to_lua(lua_State*lua_state,string argtypes,...) //!\\ it is not part of the Luacall class
{
  int nbargs=0;
  va_list varg;

  //push des valeurs de retour

  va_start(varg, argtypes); // initialisation de la liste des arguments

  // apparemment, va_start se base sur le dernier argument fice pour trouver les arguments suivants
  for(int i = 0; i < argtypes.size(); i++)
  {
    nbargs++;
    switch(argtypes[i])
    {
      case 's' :
	{
	  char* arg = va_arg(varg, char*);
	  cout << "get string arg=" << arg <<endl;
	  lua_pushstring(lua_state,arg); 
	  break;
	}
      case 'i':
	{
	  int arg = va_arg(varg,int);
	  cout << "get int arg=" << arg <<endl;
	  lua_pushnumber(lua_state, arg);
	  break;
	}
      default:
	{
	  cout << "error in argtype strings : expected types should be either 's' or 'i'" << endl;
	  exit(2);
	}
    }
  }

  va_end(varg);

  return nbargs;  // number of return values
}

char* c_str(string s)
{
  char * res = (char*)(s.c_str());
  return  res;
}


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


/****************************************
 ** Functions with integer return type **
 ****************************************/


// fonction sans argument
int Luacall::int_call(string func)
{
  return generic_int_call(func,c_str(""));
}

// fonction à 1 argument int
int Luacall::int_call(string func,int a1)
{
  return generic_int_call(func,c_str("i"),a1);
}

// fonction à 1 argument string
int Luacall::int_call(string func,string a1)
{
  return generic_int_call(func,c_str("s"),a1.c_str());
}

// argtypes string composée de "s" et de "i" par exemple pour string et int. cela donne donc "iisi" pour 4 arguments...
int Luacall::generic_int_call(string func,const char* argtypes,...)
{
  int nbargs=0;
  va_list varg;
  cout << "calling "<< func <<"("<<argtypes<<")"<<endl;
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
    argtypes++; // on va une case plus loin sur la string )))
    //va_end(varg);//was written there before but it seems to be an error..
  }
  va_end(varg);


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

/*************************************
 ** Functions with void return type **
 *************************************/

void Luacall::void_call(string func)
{
  return generic_void_call(func,c_str(""));
}


// argtypes string composée de "s" et de "i" par exemple pour string et int. cela donne donc "iisi" pour 4 arguments...
void Luacall::generic_void_call(string func,const char* argtypes,...)
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
    argtypes++; // on va une case plus loin sur la string )))
    //va_end(varg);//was written there before but it seems to be an error..
  }
  va_end(varg);


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
}


/***************************************
 ** Functions with string return type **
 ***************************************/

string Luacall::string_call(string func, string arg1, int arg2)
{
  exit(555);
  return this->generic_string_call(func,c_str("si"),arg1.c_str(),arg2);
}


string Luacall::generic_string_call(string func,string argtypes, ...)
{
  int nbargs=0;
  va_list varg;

  lua_getglobal(lua_state, func.c_str());

  //push des arguments

  va_start(varg, argtypes); // initialisation de la liste des arguments

  for(int i = 0; i < argtypes.size(); i++)
  {
    nbargs++;
    switch (argtypes[i])
    {
      case 's' :
	{
	  char* arg = va_arg(varg, char*);
	  cout << "get string arg=" << arg <<endl;
	  lua_pushstring(lua_state,arg); 
	  break;
	}
      case 'i' :
	{      
	  int arg = va_arg(varg,int);
	  cout << "get int arg=" << arg <<endl;
	  lua_pushnumber(lua_state, arg);
	  break;
	}
      default:
	{
	  cout << "error in argtype strings : expected types should be either 's' or 'i'" << endl;
	  exit(2);
	}
    }
  }
  va_end(varg);


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
  const char* retour = lua_tostring(lua_state, -1);
  lua_pop(lua_state, 1);  
  string* retour2 = new string(retour);
  return *retour2;
}

string Luacall::string_call(string func)
{
  return generic_string_call(func,c_str(""));
}
