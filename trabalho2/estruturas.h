#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>


typedef struct tipocelula *apontador;

typedef struct tipocelula{
   int elemento;
   apontador prox, ant;
 }celula;

typedef struct{
	apontador primeiro, ultimo;
}tipolista;

void flvazia(tipolista *lista);
void insere(tipolista *lista, int x);
void troca_array(int index1, int index2, int vetor[]);
void troca_lista(apontador *ptr1, apontador *ptr2);
int verifica_posicao(apontador big, apontador small);
void libera(tipolista *lista);
