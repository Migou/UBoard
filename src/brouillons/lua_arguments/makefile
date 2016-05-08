OPTS=-I/usr/include/lua5.2 -lstdc++ -Wl,--no-as-needed -ldl -llua5.2


Luacall.o: Luacall.cpp Luacall.hpp
	g++ ${OPTS} -c Luacall.cpp -o Luacall.o

call_cpp_from_lua.o: call_cpp_from_lua.cpp 
	g++ ${OPTS} -c call_cpp_from_lua.cpp -o call_cpp_from_lua.o

Luacall-test: Luacall-test.cpp Luacall.o
	g++ ${OPTS} Luacall-test.cpp Luacall.o -o Luacall-test

test: Luacall-test
	./Luacall-test
