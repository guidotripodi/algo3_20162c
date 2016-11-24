#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=-g

# Agregar acá los archivos .cpp a compilar
SOURCES=MaestroPokemon.cpp trie.cpp gym0.cpp sinOrden.cpp anillos.cpp random.cpp

# Objetos que serán generados
MAINOBJECTS=gym0.o sinOrden.o anillos.o random.o

OBJECTS=MaestroPokemon.o trie.o 
#ej3.o

# Nombre del ejecutable a generar
EXECUTABLES=gym0.test sinOrden.test anillos.test random.test

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)
