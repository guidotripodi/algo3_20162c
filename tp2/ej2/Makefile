CC=g++ -g
CFLAGS=-c -Wall

all: ej2

ej2: ejercicio2.o
	$(CC) ejercicio2.o -o ej2

ejercicio2.o: ejercicio2.cpp
	$(CC) $(CFLAGS) ejercicio2.cpp

clean:
	rm *o ej2
