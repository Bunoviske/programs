#include "estruturas.h"

void insere(tipolista vetor[], int i, int x, int p){
  //insere as aresta nas listas adjacentes de um determinado vertice
  vetor[i].ultimo->prox = (apontador) malloc(sizeof(celula));
  vetor[i].ultimo = vetor[i].ultimo->prox;
  vetor[i].ultimo->destino = x;
  vetor[i].ultimo->origem = i;
  vetor[i].ultimo->peso = p;
  vetor[i].ultimo->prox = NULL;
}

void insere_aux(tipolista *lista_aux, tipolista vetor[], int u, int flag){
  //funcao que insere as arestas do caminho na lista auxiliar
  if (flag == 1){
    apontador aux1 = vetor[u].primeiro->prox;
    lista_aux->soma = 0;
    while (u != -1) {
      while (aux1 != NULL) {
        if (aux1->destino == vetor[u].pai) {
          lista_aux->ultimo->prox = (apontador) malloc(sizeof(celula));
          lista_aux->ultimo = lista_aux->ultimo->prox;
          lista_aux->ultimo->prox = NULL;
          lista_aux->ultimo->peso = aux1->peso;
          lista_aux->ultimo->destino = aux1->origem;
          lista_aux->ultimo->origem = aux1->destino;
          lista_aux->soma = lista_aux->soma + lista_aux->ultimo->peso;
          break;
        }
        aux1 = aux1->prox;
      }
      u = vetor[u].pai;
      aux1 = vetor[u].primeiro->prox;
    }
 }
 else{
    libera_aux(lista_aux);
    flvazia(lista_aux);
    apontador aux1 = vetor[u].primeiro->prox;
    lista_aux->soma = 0;
    while (u != -1) {
      while (aux1 != NULL) {
        if (aux1->destino == vetor[u].pai) {
          lista_aux->ultimo->prox = (apontador) malloc(sizeof(celula));
          lista_aux->ultimo = lista_aux->ultimo->prox;
          lista_aux->ultimo->prox = NULL;
          lista_aux->ultimo->peso = aux1->peso;
          lista_aux->ultimo->destino = aux1->origem;
          lista_aux->ultimo->origem = aux1->destino;
          lista_aux->soma = lista_aux->soma + lista_aux->ultimo->peso;
          break;
        }
        aux1 = aux1->prox;
      }
      u = vetor[u].pai;
      aux1 = vetor[u].primeiro->prox;
    }
  }
}

void libera(tipolista vetor[], int n){
  //libera a memoria das listas adjacentes
  int i;
  apontador aux, aux1;
  for (i=0;i<n;i++){
    aux = vetor[i].primeiro;
    while (aux != NULL) {
      aux1 = aux->prox;
      free(aux);
      aux = aux1;
    }
  }
}

void libera_aux(tipolista *lista_aux){
  //libera a memoria da lista auxiliar
  apontador aux1, aux = lista_aux->primeiro;
  while (aux != NULL) {
    aux1 = aux->prox;
    free(aux);
    aux = aux1;
  }
}

void flvazia(tipolista *lista){
	//cria uma lista de ponteiros vazia
	lista->primeiro = (apontador) malloc(sizeof(celula));
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;
  lista->soma = 0;

}
void fvvazio(tipolista vetor[],int i){
  //cria um vetor vazio, que ira armazenar o grafo
  vetor[i].primeiro = (apontador) malloc(sizeof(celula));
  vetor[i].primeiro->prox = NULL;
  vetor[i].color = 'b';
  vetor[i].ultimo = vetor[i].primeiro;
}
