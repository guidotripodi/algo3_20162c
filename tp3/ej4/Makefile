CC=g++
CFLAGS= -g -std=c++11 -Wall

all: ej4

ej4: ejercicio4.o
	$(CC) $(CFLAGS) ejercicio4.o -o ej4

ejercicio4.o: ej4.cpp
	$(CC) $(CFLAGS) -c ej4.cpp -o ejercicio4.o

clean:
	rm *o ej4
