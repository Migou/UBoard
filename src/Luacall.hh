#ifndef _LUACALL_
#define _LUACALL_

#include<iostream>
#include<string>
#include<lua.hpp>
#include<lauxlib.h>
#include<lualib.h>

using namespace std; 

char* c_str(string s);
int to_lua(lua_State* l,string argtypes,...);


class Luacall {

public :
  Luacall(string luafilename);
  /************************************    
   ** CALLING LUA FUNCTIONS FROM C++ **
   ************************************/

  int int_call(string func);
  int int_call(string func, int arg1);
  int int_call(string func, string arg1);
  int generic_int_call(string func,const char* argtypes, ...);

  void void_call(string func);
  void generic_void_call(string func,const char* argtypes, ...);

  string generic_string_call(string func,string argtypes, ...);   
  string string_call(string func);
  string string_call(string func, string arg1, int arg2);

  /*
  string string_call(string func, int arg1);
  string string_call(string func, string arg1);
  */


  /************************************    
   ** CALLING C++ FUNCTIONS FROM LUA **
   ************************************/

  void make_callable_from_lua(string, int (*)(lua_State*) );
  // you will need to use "return to_lua" to return values easily
private :
  lua_State* lua_state;
};



#endif
