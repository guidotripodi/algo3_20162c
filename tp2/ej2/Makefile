CC=g++ -g
CFLAGS=-c -Wall

all: ej3

ej3: ejercicio3.o
	$(CC) ejercicio3.o -o ej3

ejercicio3.o: ejercicio3.cpp
	$(CC) $(CFLAGS) ejercicio3.cpp

clean:
	rm *o ej3
