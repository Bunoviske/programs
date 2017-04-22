#include "estruturas.h"

void flvazia(tipolista *lista){
	//cria uma lista de ponteiros vazia
	lista->primeiro = (apontador) malloc(sizeof(celula));
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;
	lista->primeiro->ant = NULL;
}

void insere(tipolista *lista, int x){
	//insere um elemento na lista
		lista->ultimo->prox = (apontador) malloc(sizeof(celula));
		lista->ultimo->prox->ant = lista->ultimo;
		lista->ultimo = lista->ultimo->prox;
		lista->ultimo->prox = NULL;
		lista->ultimo->elemento = x;

}

void libera(tipolista *lista){
	//libera os elementos da lista
	apontador aux=lista->primeiro, aux1 = aux->prox;
	while (aux1 != NULL){
		free(aux);
		aux = aux1;
		aux1 = aux1->prox;
	}
	free(aux);
}


void troca_array(int index1, int index2, int vetor[]){
	//troca dois elementos de posicao de um array
  int aux;
  aux = vetor[index1];
  vetor[index1] = vetor[index2];
  vetor[index2] = aux;
}

void troca_lista(apontador *ptr1, apontador *ptr2){
	//troca de posicao dois elementos de uma lista duplamente encadeada
	apontador proximo;
	apontador anterior;

	if ((*ptr1)->prox != *ptr2) {
		//caso em que dois elementos nao sao adjacentes
		anterior = (*ptr1)->ant;
		proximo = (*ptr1)->prox;

		(*ptr1)->prox = (*ptr2)->prox;
		(*ptr1)->ant = (*ptr2)->ant;
	  (*ptr1)->ant->prox = *ptr1 ;
		if ((*ptr1)->prox != NULL){
			(*ptr1)->prox->ant = *ptr1 ;
		}

		(*ptr2)->prox = proximo;
		(*ptr2)->ant = anterior;
		(*ptr2)->ant->prox = (*ptr2);
		if ((*ptr2)->prox != NULL){
			(*ptr2)->prox->ant = *ptr2 ;
		}
	}
	//caso em que dois elementos da lista sao adjacentes
	else{
		anterior = (*ptr1)->ant;

		(*ptr1)->prox = (*ptr2)->prox;
		(*ptr1)->ant = (*ptr2);
		if ((*ptr1)->prox != NULL){
			(*ptr1)->prox->ant = *ptr1 ;
		}

		(*ptr2)->prox = *ptr1;
		(*ptr2)->ant = anterior;
		(*ptr2)->ant->prox = *ptr2;


	}
	/*variavel usada apenas como auxiliar, ja que o big index e o small index
	devem manter a mesma posicao*/
	anterior = (*ptr1);
	(*ptr1) = (*ptr2);
	(*ptr2) = anterior;


}

int verifica_posicao(apontador big, apontador small){
	//funcao que verifica se o ponteiro small ultrapassou o ponteiro big, da funcao Quicksort_lista
	if (small->prox == big) {
		return 1;
	}
	else{
		return 0;
	}
}
