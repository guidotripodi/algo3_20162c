CC=g++ -g
CFLAGS=-c -Wall -std=c++11

all: ej1

ej1: ejercicio1.o
	$(CC) ejercicio1.o -o ej1

ejercicio1.o: ejercicio1.cpp
	$(CC) $(CFLAGS) ejercicio1.cpp

clean:
	rm *o ej1
