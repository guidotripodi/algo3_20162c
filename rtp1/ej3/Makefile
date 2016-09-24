# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio3.cpp 

# Objetos que serán generados
OBJECTS=ejercicio3.o 

# Nombre del ejecutable a generar
EXECUTABLE=ej3

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
