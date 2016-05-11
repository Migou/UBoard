#include <stdlib.h> // exit
#include <iostream>
#include <string>
#include <sstream> // int 2 string conversion


using namespace std;

void die(string mess){
  cerr << mess << endl;
  exit(1);
}

string my_int_to_string(int i)
{
string res;          // string which will contain the result
ostringstream convert;   // stream used for the conversion
convert << i;      // insert the textual representation of 'Number' in the characters in the stream

return convert.str(); // set 'Result' to the contents of the stream
}

