#ifndef _LUACALL_
#define _LUACALL_

#include<iostream>
#include<lua.hpp>
#include<lauxlib.h>
#include<lualib.h>

using namespace std; 

class Luacall {

public :
  Luacall(string luafilename);
  int int_call(string func);
  int int_call(string func, int arg1);
  int int_call(string func, string arg1);
  int generic_int_call(string func,const char* argtypes, ...);

  string generic_string_call(string func,const char* argtypes, ...);   
  string string_call(string func);
  /*
  string string_call(string func, int arg1);
  string string_call(string func, string arg1);
  */

private :
  lua_State* lua_state;
};



#endif
