#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -ggdb -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej4.cpp MaestroPokemon.cpp trie.cpp gym0.cpp todosGym0.cpp orden.cpp sinOrden.cpp anillos.cpp SetTabu.cpp randomRtp.cpp

# Objetos que serán generados
MAINOBJECTS=gym0.o todosGym0.o orden.o sinOrden.o anillos.o randomRtp.o

OBJECTS=MaestroPokemon.o trie.o SetTabu.o ej4.o

# Nombre del ejecutable a generar
EXECUTABLES=gym0.test todosGym0.test orden.test sinOrden.test anillos.test randomRtp.test

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)
