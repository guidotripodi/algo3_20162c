# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio1.cpp sinRomperParedes.cpp rompiendoPparedes.cpp sinSolucion.cpp complejidad.cpp pParedes.cpp

# Objetos que serán generados
OBJECTS=ejercicio1.o 
OBJECTS1 = sinRomperParedes.o 
OBJECTS2 = rompiendoPparedes.o 
OBJECTS3 = sinSolucion.o
OBJECTS4 = complejidad.o
OBJECTS5 = pParedes.o

# Nombre del ejecutable a generar
EXECUTABLE=ej1 sinRomperParedes rompiendoPparedes sinSolucion complejidad pParedes

all: $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(OBJECTS5)

ej1: ejercicio1.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $@		

sinRomperParedes: sinRomperParedes.o
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@				

rompiendoPparedes: rompiendoPparedes.o
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

sinSolucion: sinSolucion.o
	$(CC) $(CFLAGS) $(OBJECTS3) -o $@

complejidad: complejidad.o
	$(CC) $(CFLAGS) $(OBJECTS4) -o $@

pParedes: pParedes.o
	$(CC) $(CFLAGS) $(OBJECTS5) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
