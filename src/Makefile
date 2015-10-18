mew: 
	./miaou

utils.o : utils.cpp
	g++ -c utils.cpp

ia.o : ia.cpp
	g++ -c ia.cpp

ia_utest: mew ia_utest.cpp utils.o ia.o 
	g++ ia_utest.cpp ia.o utils.o -o ia_iutest
