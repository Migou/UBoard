DEBUGOPT=-g

mew:
	miaou

utils.o : mew utils.cpp utils.hh
	g++ ${DEBUGOPT} -Wall -c utils.cpp -o utils.o

IA.o : mew IA.cpp IA.hh
	g++ ${DEBUGOPT} -Wall -c IA.cpp -o IA.o

Grid.o : mew Grid.hh
	g++ ${DEBUGOPT} -Wall -c Grid.cpp -o Grid.o

LogicalBoard.o : mew LogicalBoard.hh LogicalBoard.cpp
	g++ ${DEBUGOPT} -Wall -c LogicalBoard.cpp -o LogicalBoard.o

Player.o : mew Player.hh Player.cpp
	g++ ${DEBUGOPT} -Wall -c Player.cpp -o Player.o
HumanPlayer.o : mew Player.hh Player.cpp
	g++ ${DEBUGOPT} -Wall -c HumanPlayer.cpp -o HumanPlayer.o


ActionAllumettes.o : mew ActionAllumettes.cpp ActionAllumettes.hh
	g++ ${DEBUGOPT} -Wall -c ActionAllumettes.cpp -o ActionAllumettes.o

Coup.o : mew Coup.cpp Coup.hh
	g++ ${DEBUGOPT} -Wall -c Coup.cpp -o Coup.o

State.o : mew State.cpp State.hh
	g++ ${DEBUGOPT} -Wall -c State.cpp -o State.o

test : mew State.o Coup.o utils.o test.cpp
	g++ ${DEBUGOPT} -Wall test.cpp State.o Coup.o utils.o -o test

ia_coup_test : mew ia_coup_test.cpp LogicalBoard.o Grid.o utils.o IA.o Player.o ActionAllumettes.o Coup.o State.o HumanPlayer.o 
	g++ ${DEBUGOPT} -Wall ia_coup_test.cpp utils.o IA.o Player.o ActionAllumettes.o Coup.o State.o HumanPlayer.o Grid.o LogicalBoard.o -o ia_coup_test
