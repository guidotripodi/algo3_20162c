#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej3.cpp MaestroPokemon.cpp trie.cpp gym0.cpp sinOrden.cpp todosGym0.cpp anillos.cpp

# Objetos que serán generados
MAINOBJECTS=gym0.o sinOrden.o todosGym0.o anillos.o 

OBJECTS=MaestroPokemon.o trie.o 
#ej3.o

# Nombre del ejecutable a generar
EXECUTABLES=gym0.test sinOrden.test todosGym0.test anillos.test

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)
