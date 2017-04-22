main: main.o logica.o in_out.o lista.o
	gcc logica.o main.o in_out.o lista.o -o main
main.o: main.c logica.h lista.h
	gcc -g -c main.c
logica.o: logica.c logica.h 
	gcc -g -c logica.c 	
in_out.o: in_out.c in_out.h 
	gcc -g -c in_out.c
lista.o: lista.c lista.h
	gcc -g -c lista.c