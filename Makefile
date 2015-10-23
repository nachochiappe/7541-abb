#Makefile - Arbol Binario de Busqueda

#Variables:
EXEC=abb
CC=gcc
CFLAGS= -std=c99 -g -Wall -Wconversion -Wtype-limits -pedantic -Werror
OBJECTS=main.o abb.o pila.o pruebas_alumno.o testing.o
VALGRIND= valgrind --leak-check=full --track-origins=yes

all: $(EXEC)

abb.o: abb.c abb.h
	$(CC) $(CFLAGS) -c abb.c
	
pruebas_alumno.o: pruebas_alumno.c
	$(CC) $(CFLAGS) -c pruebas_alumno.c

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

valgrind: $(EXEC)
	$(VALGRIND) ./$(EXEC)

clean: 
	rm -f *.o *~
