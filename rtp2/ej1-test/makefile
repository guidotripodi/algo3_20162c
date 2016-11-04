# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio1.cpp sinRomperParedes.cpp rompiendoPparedes.cpp sinSolucion.cpp pParedes.cpp pParedesUt.cpp

# Objetos que serán generados
OBJECTS1 = sinRomperParedes.o 
OBJECTS2 = rompiendoPparedes.o 
OBJECTS3 = sinSolucion.o
OBJECTS5 = pParedes.o
OBJECTS6 = pParedesUt.o

# Nombre del ejecutable a generar
EXECUTABLE=sinRomperParedes rompiendoPparedes sinSolucion pParedes pParedesUt

all: $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS5) $(OBJECTS6)

sinRomperParedes: sinRomperParedes.o
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@				

rompiendoPparedes: rompiendoPparedes.o
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

sinSolucion: sinSolucion.o
	$(CC) $(CFLAGS) $(OBJECTS3) -o $@

pParedes: pParedes.o
	$(CC) $(CFLAGS) $(OBJECTS5) -o $@

pParedesUt: pParedesUt.o
	$(CC) $(CFLAGS) $(OBJECTS6) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
