CC = gcc
C_FLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
DEFAULT = TPCola
OBJ_COLA = cola.o
OBJ_PILA = pila.o
OBJ_TESTING  = testing.o
OBJS =  cola.o pila.o testing.o
VALGRIND = valgrind
V_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

all: $(DEFAULT)

$(DEFAULT): $(OBJS)
		$(CC) $(C_FLAGS) main.c $(OBJS) pruebas_alumno.c  -o $(DEFAULT)

$(OBJ_COLA): cola.c cola.h
		$(CC) $(C_FLAGS) cola.c -c

$(OBJ_PILA): pila.c pila.h
		$(CC) $(C_FLAGS) pila.c -c

$(OBJ_TESTING): testing.c testing.h
		$(CC) $(C_FLAGS) testing.c -c

run: $(DEFAULT)
		$(VALGRIND) $(V_FLAGS) ./$(DEFAULT)

clean_obj:
		rm -f *.o

clean: clean_obj
		rm -f $(DEFAULT)
