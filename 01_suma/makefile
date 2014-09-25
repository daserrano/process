#makefile para sumar, v1
#usar tabulador en la linea de comando

CC = gcc
.SUFFIXES: .o .cpp
.cpp.o:
	$(CC) -c $<

OBJECTS = suma.o 

suma :	main.o $(OBJECTS)
	$(CC) -o suma main.o $(OBJECTS)

main.o:	library.hpp
	$(CC) -c main.c

suma.o:	library.hpp
	$(CC) -c suma.cpp

.PHONY : clean
clean:
	-rm suma main.o $(OBJECTS)
