#include<iostream>
#include<lua.hpp>
#include<lauxlib.h>
#include<lualib.h>

// Pour installer les librairies lua 5.2 :
//   sudo apt-get install liblua5.2-dev
//g++ 05-Cpp_communication.cpp -I/usr/include/lua5.2 -llua5.2
//     ou
//g++ 05-Cpp_communication.cpp -I/usr/include/lua5.2 -lstdc++ -Wl,--no-as-needed -ldl -llua5.2
//
// NB : le nom du fichier lua est indiqué dans le fichier cpp, dans 



using namespace std;

int main(int argc, char* argv[])
{
	lua_State * lua_state=luaL_newstate();
	luaL_openlibs(lua_state);
	if(luaL_dofile(lua_state,"./hello.lua")==1)
	{
		cout << "erreur à l'ouverture du fichier" <<endl;

		return 1;
	}
	else
	{
		string langue[3];
		langue[0]="francais";
		langue[1]="english";
		langue[2]="bjkhqrt";

		for(int i = 0; i < 3; ++i)
		{
			cout << "C++ - Langue : " << langue[i]<<endl;
			/* push functions and arguments */
			lua_getglobal(lua_state, "func_hello");  /* function to be called */
			lua_pushstring(lua_state, langue[i].c_str());   /* push 1st argument */
			//lua_pushnumber(lua_state, y);   /* push 2nd argument */

			/* do the call (1 arguments, 1 result) */
			if (lua_pcall(lua_state, 1, 1, 0) != 0)
			{
				cout << "impossible de lancer la fonction" << endl;
				return 2;
			}

			/* retrieve result */
			if (!lua_isnumber(lua_state, -1))
			{
				cout << "function `func_hello' must return a number" << endl;
				return 3;
			}
			int retour = lua_tonumber(lua_state, -1);
			lua_pop(lua_state, 1);  /* pop returned value */

			if(retour==0)
			{
				cout << "C++ - langue connue" << endl << endl;
			}
			else
			{
				cout << "C++ - langue inconnue" << endl << endl;
			}
		}
	}


	/* 
	 * Test d'une fonction qui retourne plusieurs valeurs
	 */


	// function name
	lua_getglobal(lua_state, "retours_multiples");  

	//argument 1
	lua_pushnumber(lua_state, 7);  
	
	//argument 2
	//lua_pushnumber(lua_state, 10); 
	
	// do the call (1 arg 2 results
	if (lua_pcall(lua_state, 1, 2, 0) != 0)
	{
	  cout << "impossible de lancer la fonction" << endl;
	  return 2;
	}
			
	// retrieve result 
	if (!lua_isnumber(lua_state, -2))
	{
	  cout << "function `retours_multiples' : return value 1 missing" << endl;
	  return 3;
	}

	if (!lua_isnumber(lua_state, -1))
	{
	  cout << "function `retours_multiples' : return value 2 missing" << endl;
	  return 3;
	}

	// notez bien l'ordre des valeurs de retour : la valeur de retour 1 est sous la valeur 2 dans la pile d'appels. ce qui est logique!
	int r1 = lua_tonumber(lua_state, -2);
	int r2 = lua_tonumber(lua_state, -1);

	cout << "recu "<<r1<<", "<<r2<<endl;

	// on dépile les 2 valeurs de retour. merci les cours de l'école d'ingé.
	lua_pop(lua_state, 2);  

	return 0;
}
