# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio3.cpp mismasMochilas.cpp noEntranObjetos.cpp

# Objetos que serán generados
OBJECTS=ejercicio3.o 
OBJECTS1=mismasMochilas.o 
OBJECTS2=noEntranObjetos.o 

# Nombre del ejecutable a generar
EXECUTABLE=ej3 mismasMochilas noEntranObjetos

all: $(EXECUTABLE)

ej3: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

mismasMochilas: $(OBJECTS1) 
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@

noEntranObjetos: $(OBJECTS2) 
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) $(OBJECTS1) $(OBJECTS2)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
