CC=g++ 
CFLAGS=-g -Wall
OBJECTS=ejercicio3.o grafo.o

all: ej3

ej3: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ej3

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@


clean:
	rm *o ej3
