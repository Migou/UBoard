OPTS=-I/usr/include/lua5.2 -lstdc++ -Wl,--no-as-needed -ldl -llua5.2

Luacall-test: Luacall-test.cpp Luacall.o
	g++ ${OPTS} Luacall-test.cpp Luacall.o -o Luacall-test

Luacall.o: Luacall.cpp Luacall.hpp
	g++ ${OPTS} -c Luacall.cpp -o Luacall.o

