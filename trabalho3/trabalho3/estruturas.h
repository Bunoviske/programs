#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>






typedef struct tipocelula *apontador;

typedef struct tipocelula{
   int origem,destino, peso;
   apontador prox;
 }celula;

 typedef struct{
  char color;
  int pai;
  int soma;
 	apontador primeiro, ultimo;
 }tipolista;

void insere(tipolista vetor[], int i, int x, int p);
void insere_aux(tipolista *lista_aux, tipolista vetor[], int u, int flag);
void libera(tipolista vetor[], int n);
void libera_aux(tipolista *lista_aux);
void flvazia(tipolista *lista);
void fvvazio(tipolista vetor[],int i);
