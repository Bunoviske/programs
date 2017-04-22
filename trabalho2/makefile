main: main.o logica.o out_in.o estruturas.o
	gcc logica.o main.o out_in.o estruturas.o -o main
main.o: main.c logica.h estruturas.h
	gcc -g -c main.c
logica.o: logica.c logica.h 
	gcc -g -c logica.c 	
out_in.o: out_in.c out_in.h 
	gcc -g -c out_in.c
estruturas.o: estruturas.c estruturas.h
	gcc -g -c estruturas.c