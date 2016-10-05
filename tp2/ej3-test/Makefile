CC=g++ 
CFLAGS=-g -Wall
MAINOBJECTS=ejercicio3.o sinSolucion.o caminoSimple.o sinEjes.o
OBJECTS=grafo.o

EXECUTABLES= ejercicio3 sinSolucion caminoSimple sinEjes

all: $(EXECUTABLES)

ejercicio3: $(OBJECTS) ejercicio3.o  
	$(CC) $(CFLAGS) $^ -o $@

sinSolucion: $(OBJECTS) sinSolucion.o 
	$(CC) $(CFLAGS) $^ -o $@ 

caminoSimple: $(OBJECTS) caminoSimple.o 
	$(CC) $(CFLAGS) $^ -o $@ 

sinEjes: $(OBJECTS) sinEjes.o
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@


clean:
	rm $(OBJECTS) $(MAINOBJECTS) $(EXECUTABLES) 
