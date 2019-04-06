CC := g++
CFLAGS := --std=c++11 -Wall -O
LDFLAGS := -Wall

tautology: main.o Util.o 
	${CC} ${CFLAGS} main.o Util.o -o tautology

main.o: main.cpp
	${CC} ${LDFLAGS} -c main.cpp

Util.o: Util.cpp Util.h
	${CC} ${LDFLAGS} -c Util.cpp

clear:
	rm *.o
