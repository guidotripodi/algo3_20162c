# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ej1.cpp Escenario2.cpp trie.cpp

# Objetos que serán generados
MAINOBJECTS=ej1.o

OBJECTS=Escenario2.o trie.o

# Nombre del ejecutable a generar
EXECUTABLES=ej1

all: $(EXECUTABLES)

#Para agregar ejecutables. Agregar a EXECUTABLES y MAINOBJECTS
ej1: $(OBJECTS) ej1.o  
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(EXECUTABLES) $(MAINOBJECTS) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
