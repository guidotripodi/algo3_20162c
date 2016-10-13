#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej1.cpp Escenario2.cpp trie.cpp

# Objetos que serán generados
MAINOBJECTS=ej1.o velocidadesDistintas.o noHayCanibales.o velocidadesIguales.o 1Arq2can.o 2Arq1can.o masArq.o sinSolucion.o complejidad.o

OBJECTS=Escenario2.o trie.o

# Nombre del ejecutable a generar
EXECUTABLES=ej1.test velocidadesDistintas.test noHayCanibales.test velocidadesIguales.test 1Arq2can.test 2Arq1can.test masArq.test sinSolucion.test complejidad.test

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)
