CC=g++
CFLAGS=-g -Wall
CXXFLAGS=-I include
LDDIR=-L lib
LIBA=-lPDDL

all: executor.o
	$(CC) executor.o lib/libPDDL.so -o bin/pddl_executor

executor.o: src/executor.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) src/executor.cpp -c


clean: deltemp
	rm bin/pddl_executor
	find -name "*.o" -exec rm {} \;

deltemp:
	find -name "*~" -exec rm {} \;

