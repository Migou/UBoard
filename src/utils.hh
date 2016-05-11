#ifndef _vjbb_utils__
#define _vjbb_utils__

// Macros pour l'affichage de vecteurs contenant des types de base
#define PRINTVECT(v) for( unsigned int xx_vb_index=0; xx_vb_index<v.size(); ++xx_vb_index) std::cout << v[xx_vb_index] << ' '; cout<<endl;
#define PRINTVECTPREFIX(v, prefix) for( unsigned int xx_vb_index=0; xx_vb_index<v.size(); ++xx_vb_index) std::cout << prefix <<v[xx_vb_index] << ' '; cout<<endl;

// Macros pour l'affichage de vecteurs contenant des objets implémentant la méthode toString()
#define PRINTVECTPREFIX_toString(v,prefix) for(unsigned int xx_vb_index=0; xx_vb_index<v.size(); ++xx_vb_index) std::cout << prefix << v[xx_vb_index]->toString() << ' '; cout<<endl;
#define PRINTVECT_toString(v) for(unsigned int xx_vb_index=0; xx_vb_index<v.size(); ++xx_vb_index) std::cout <<[xx_vb_index]->toString() << ' '; cout<<endl;


#include<iostream>
using namespace std;

void die(string);

string my_int_to_string(int);

#endif
