# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ejercicio2.cpp ciclosvarios.cpp grafoAGM.cpp sinsolucion.cpp costo0.cpp complejidad.cpp

# Objetos que serán generados
OBJECTS=ejercicio2.o 
OBJECTS1 = ciclosvarios.o 
OBJECTS2 = grafoAGM.o 
OBJECTS3 = sinsolucion.o
OBJECTS4 = costo0.o
OBJECTS5 = complejidad.o

# Nombre del ejecutable a generar
EXECUTABLE=ej2 ciclosvarios grafoAGM sinsolucion costo0 complejidad

all: $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

ej2: ejercicio2.o
	$(CC) $(CFLAGS) $(OBJECTS) -o $@		

ciclosvarios: ciclosvarios.o
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@				

grafoAGM: grafoAGM.o
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

sinsolucion: sinsolucion.o
	$(CC) $(CFLAGS) $(OBJECTS3) -o $@

costo0: costo0.o
	$(CC) $(CFLAGS) $(OBJECTS4) -o $@

complejidad: complejidad.o
	$(CC) $(CFLAGS) $(OBJECTS5) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
