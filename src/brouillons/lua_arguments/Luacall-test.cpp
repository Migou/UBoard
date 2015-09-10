#include "Luacall.hpp"
#include<iostream>

int main(int argc, char** argv){

  Luacall lc = Luacall("./luacalltest.lua");

  int res1 = lc.int_call("func_int_noarg");
  cout << "resultat=" << res1 << endl;

  int res2 = lc.int_call("func_int_fois_deux",15);
  cout << "resultat=" << res2 << endl;

  string s = "Bonjour";
  int res3 = lc.int_call("strlen",s);
  cout << "longueur(" <<s<<")="<< res3 << endl;
  
}
