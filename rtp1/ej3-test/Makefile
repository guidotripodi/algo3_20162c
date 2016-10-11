# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio3.cpp soloUno.cpp noEntranObjetos.cpp todosAdentro.cpp unSoloObjetoXMochila.cpp cantidadDispar.cpp cantidadPar.cpp 

# Objetos que serán generados
OBJECTS=ejercicio3.o 
OBJECTS1=soloUno.o 
OBJECTS2=noEntranObjetos.o 
OBJECTS4=todosAdentro.o 
OBJECTS5=unSoloObjetoXMochila.o 
OBJECTS6=cantidadPar.o 
OBJECTS7=cantidadDispar.o 

# Nombre del ejecutable a generar
EXECUTABLE=ej3 soloUno noEntranObjetos todosAdentro unSoloObjetoXMochila cantidadDispar cantidadPar

all: $(EXECUTABLE)

ej3: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

soloUno: $(OBJECTS1) 
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@

noEntranObjetos: $(OBJECTS2) 
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

todosAdentro: $(OBJECTS4) 
	$(CC) $(CFLAGS) $(OBJECTS4) -o $@

unSoloObjetoXMochila: $(OBJECTS5) 
	$(CC) $(CFLAGS) $(OBJECTS5) -o $@

cantidadPar: $(OBJECTS6) 
	$(CC) $(CFLAGS) $(OBJECTS6) -o $@

cantidadDispar: $(OBJECTS7) 
	$(CC) $(CFLAGS) $(OBJECTS7) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(OBJECTS1) $(OBJECTS2) $(OBJECTS4) $(OBJECTS5) $(OBJECTS6) $(OBJECTS7) 

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
