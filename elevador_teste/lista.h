#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>
   
typedef struct tipocelula *apontador;    

typedef struct tipocelula{
   int andar_chamada, andar_destino, andar_dest, tempo_chamada;
   int tempo_entrada, tempo_saida;
   apontador prox;
 }celula;

typedef struct{
	apontador primeiro, ultimo;
}tipolista;

typedef struct{
	int andar_atual, andar_max, cap_max, cap_atual;
	char direcao;
}tipoelevador;

void flvazia(tipolista *lista);
int insere(FILE *fp, tipolista *lista);
void insere_listaposterior(tipolista *listaposterior, apontador aux);
void transforma_lista(tipolista *listaacao, tipolista *listaposterior);
void insereacao(tipolista *lista,tipolista *listaacao);
void ordena_crescente(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior);
void ordena_decrescente(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior);
void ordena_tempo(tipolista *lista);
apontador libera(apontador anterior, apontador aux1);
void desaloca(tipolista *lista);

