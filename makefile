CC=g++
CFLAGS=-g -Wall
CXXFLAGS=-I include
LDDIR=-L lib
LIBA=-lPDDL

all: 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDDIR) $(LIBA) src/executor.cpp -o bin/pddl_executor

clean: deltemp
	rm bin/pddl_executor
	find -name "*.o" -exec rm {} \;

deltemp:
	find -name "*~" -exec rm {} \;

