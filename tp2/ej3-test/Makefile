CC=g++ 
CFLAGS=-g -Wall -std=c++11
MAINOBJECTS=ejercicio3.o sinSolucion.o caminoSimple.o sinEjes.o casoRandom.o peorCaso.o
OBJECTS=grafo.o

EXECUTABLES= ejercicio3 sinSolucion peorCaso caminoSimple sinEjes casoRandom

all: $(EXECUTABLES)

ejercicio3: $(OBJECTS) ejercicio3.o  
	$(CC) $(CFLAGS) $^ -o $@

sinSolucion: $(OBJECTS) sinSolucion.o 
	$(CC) $(CFLAGS) $^ -o $@ 

caminoSimple: $(OBJECTS) caminoSimple.o 
	$(CC) $(CFLAGS) $^ -o $@ 

sinEjes: $(OBJECTS) sinEjes.o
	$(CC) $(CFLAGS) $^ -o $@ 

casoRandom: $(OBJECTS) casoRandom.o
	$(CC) $(CFLAGS) $^ -o $@ 

peorCaso: $(OBJECTS) peorCaso.o
	$(CC) $(CFLAGS) $^ -o $@ 
%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@


clean:
	rm $(OBJECTS) $(MAINOBJECTS) $(EXECUTABLES) 
