# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall -std=c++11

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=ciclosvarios.cpp grafoAGM.cpp sinsolucion.cpp costo0.cpp sinEjes.cpp

# Objetos que serán generados
OBJECTS1 = ciclosvarios.o 
OBJECTS2 = grafoAGM.o 
OBJECTS3 = sinsolucion.o
OBJECTS4 = costo0.o
OBJECTS5 = sinEjes.o

# Nombre del ejecutable a generar
EXECUTABLE=ciclosvarios grafoAGM sinsolucion costo0 sinEjes

all: $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS1) $(OBJECTS2) $(OBJECTS3) $(OBJECTS4) $(OBJECTS5)

ciclosvarios: ciclosvarios.o
	$(CC) $(CFLAGS) $(OBJECTS1) -o $@				

grafoAGM: grafoAGM.o
	$(CC) $(CFLAGS) $(OBJECTS2) -o $@

sinsolucion: sinsolucion.o
	$(CC) $(CFLAGS) $(OBJECTS3) -o $@

costo0: costo0.o
	$(CC) $(CFLAGS) $(OBJECTS4) -o $@

sinEjes: sinEjes.o
	$(CC) $(CFLAGS) $(OBJECTS5) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@
