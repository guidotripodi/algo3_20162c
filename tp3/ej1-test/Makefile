#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej1.cpp MaestroPokemon.cpp trie.cpp orden.cpp sinOrden.cpp gym0.cpp

# Objetos que serán generados
MAINOBJECTS=ej1.o sinSolucionPorPP.o sinSolucionPorCapMochila.o orden.o sinOrden.o gym0.o

OBJECTS=MaestroPokemon.o trie.o

# Nombre del ejecutable a generar
EXECUTABLES=ej1.test sinSolucionPorPP.test sinSolucionPorCapMochila.test orden.test sinOrden.test gym0.test

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)