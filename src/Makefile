DEBUGOPT=-g

mew: 
	./miaou

utils.o : utils.cpp
	g++ ${DEBUGOPT} -c utils.cpp

State.o: State.cpp State.hh
	g++ ${DEBUGOPT} -c State.cpp

Coup.o:
	g++ ${DEBUGOPT} -c Coup.cpp

ia.o : ia.cpp
	g++ ${DEBUGOPT} -c ia.cpp

ia_utest.o: mew ia_utest.cpp 
	g++ ${DEBUGOPT} -c -Wall ia_utest.cpp -o ia_utest.o

ia_utest: mew ia_utest.o utils.o ia.o 
	g++ ${DEBUGOPT} -Wall -Wextra ia_utest.o ia.o utils.o -o a.out

ia_coup_test.o: ia_coup_test.cpp
	g++ ${DEBUGOPT} -c -Wall ia_coup_test.cpp -o ia_coup_test.o

ia_coup_test: mew ia_coup_test.o utils.o ia.o Coup.o
	g++ ${DEBUGOPT} -Wall -Wextra ia_coup_test.o ia.o utils.o Coup.o -o a.out
