#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS

# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej3.cpp MaestroPokemon.cpp trie.cpp orden.cpp sinOrden.cpp gym0.cpp todosGym0.cpp

# Objetos que serán generados
MAINOBJECTS= anillos.o sinSolucionPorPP.o sinSolucionPorCapMochila.o orden.o sinOrden.o gym0.o todosGym0.o

OBJECTS=MaestroPokemon.o trie.o 
#ej3.o

# Nombre del ejecutable a generar
EXECUTABLES=orden.test todosGym0.test sinOrden.test gym0.test anillos.test
#sinSolucionPorPP.test sinSolucionPorCapMochila.test 

all: $(EXECUTABLES)

%.test: $(OBJECTS) %.o  
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)
