#include "Luacall.hpp"
#include<iostream>
using namespace std;

int f1(lua_State *l){
  int argc = lua_gettop(l);
  cout <<  "Lua vient de nous appeler. nbargs=" << argc << endl;

  char s[8] = "Vincent"; // too bad, I have no ideat how to make a char* in one line
  return to_lua(l,"is",666,c_str("Vincent"));
}

int main(int argc, char** argv){

  Luacall lc = Luacall("./luacalltest.lua");

  lc.make_callable_from_lua("appel_au_c",f1);
  
  lc.void_call("second_hand_main");

  int res1 = lc.int_call("func_int_noarg");
  cout << "resultat=" << res1 << endl;

  int res2 = lc.int_call("func_int_fois_deux",15);
  cout << "resultat=" << res2 << endl;

  string s = "Bonjour";
  int res3 = lc.int_call("strlen",s);
  cout << "longueur(" <<s<<")="<< res3 << endl;

  string res4 = lc.string_call("defaultstring");
  cout << ""<< res4 << endl;

  string res5 = lc.string_call("makelogin","vincent",66);
  cout << "Login créé : "<< res5 << endl;
}
