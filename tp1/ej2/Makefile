# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES=main.cpp balanza.cpp

# Objetos que serán generados
OBJECTS=main.o balanza.o

# Nombre del ejecutable a generar
EXECUTABLE=ej2

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

%.cpp: %.o
	$(CC) $(CFLAGS) $< -c -o $@
