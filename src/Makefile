DEBUGOPT=-g
LUAOPTS=-I/usr/include/lua5.2 -lstdc++ -Wl,--no-as-needed -ldl -llua5.2

mew:
	miaou

utils.o : mew utils.cpp utils.hh
	g++ ${DEBUGOPT} -Wall -c utils.cpp -o utils.o

IA.o : mew IA.cpp IA.hh
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c IA.cpp -o IA.o

Grid.o : mew Grid.hh
	g++ ${DEBUGOPT} -Wall -c Grid.cpp -o Grid.o

LogicalBoard.o : mew LogicalBoard.hh LogicalBoard.cpp
	g++ ${DEBUGOPT} -Wall -c LogicalBoard.cpp -o LogicalBoard.o

Player.o : mew Player.hh Player.cpp
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c Player.cpp -o Player.o

HumanPlayer.o : mew Player.hh Player.cpp
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c HumanPlayer.cpp -o HumanPlayer.o


ActionAllumettes.o : mew ActionAllumettes.cpp ActionAllumettes.hh
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c ActionAllumettes.cpp -o ActionAllumettes.o

Coup.o : mew Coup.cpp Coup.hh
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c Coup.cpp -o Coup.o

State.o : mew State.cpp State.hh
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c State.cpp -o State.o

LuaCall.o: LuaCall.cpp
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall -c LuaCall.cpp -o LuaCall.o

test : mew State.o Coup.o utils.o test.cpp
	g++ ${DEBUGOPT} -Wall test.cpp State.o Coup.o utils.o -o test

LuaCall-test : LuaCall-test.cpp LuaCall.o Coup.o utils.o ActionAllumettes.o State.o LogicalBoard.o Grid.o IA.o Player.o HumanPlayer.o
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall ./LuaCall-test.cpp LuaCall.o Coup.o utils.o ActionAllumettes.o State.o LogicalBoard.o Grid.o IA.o Player.o HumanPlayer.o -o LuaCall-test

ia_coup_test : mew ia_coup_test.cpp LuaCall.o LogicalBoard.o Grid.o utils.o IA.o Player.o ActionAllumettes.o Coup.o State.o HumanPlayer.o
	g++ ${DEBUGOPT} ${LUAOPTS} -Wall ia_coup_test.cpp utils.o IA.o Player.o ActionAllumettes.o Coup.o State.o HumanPlayer.o Grid.o LogicalBoard.o LuaCall.o -o ia_coup_test
