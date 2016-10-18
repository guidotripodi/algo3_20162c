CC=g++
CFLAGS= -g -std=c++11 -Wall

all: ej3

ej3: ejercicio3.o
	$(CC) $(CFLAGS) ejercicio3.o -o ej3

ejercicio3.o: ej3.cpp
	$(CC) $(CFLAGS) -c ej3.cpp -o ejercicio3.o

clean:
	rm *o ej3
