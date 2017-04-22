main: main.o logica.o in_out.o estruturas.o
	gcc logica.o main.o in_out.o estruturas.o -o main
main.o: main.c logica.h estruturas.h
	gcc -g -c main.c
logica.o: logica.c logica.h 
	gcc -g -c logica.c 	
in_out.o: in_out.c in_out.h 
	gcc -g -c in_out.c
estruturas.o: estruturas.c estruturas.h
	gcc -g -c estruturas.c