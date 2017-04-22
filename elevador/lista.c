#include "lista.h"

void flvazia(tipolista *lista){
	//cria uma lista de ponteiros vazia
	lista->primeiro = (apontador) malloc(sizeof(celula));
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;

}

int insere(FILE *fp, tipolista *lista){
	//insere um elemento na lista, recebendo os dados do arquivo texto de entrada
	apontador aux;
	int aux1;
	if (fscanf(fp, "%d\n", &aux1) != EOF){
		aux = lista->ultimo;
		lista->ultimo->prox = (apontador) malloc(sizeof(celula));
		lista->ultimo = lista->ultimo->prox;
		lista->ultimo->prox = NULL;
		lista->ultimo->andar_chamada = aux1;
		fscanf(fp, "%d\n", &lista->ultimo->andar_destino);
		fscanf(fp, "%d\n", &lista->ultimo->tempo_chamada);
		return 1;
	}
	else{
		return 0;
	}
	
}

void insere_listaposterior(tipolista *listaposterior, apontador aux){
	//insere uma celula na lista posterior de acoes do elevador
	apontador aux1 = listaposterior->primeiro->prox;
	listaposterior->primeiro->prox = aux;
	listaposterior->primeiro->prox->prox = aux1;

}				

void transforma_lista(tipolista *listaacao, tipolista *listaposterior){
	//transforma a lista posterior na lista de acoes do elevador
	apontador aux, aux1;
	while(listaposterior->primeiro->prox != NULL){
		aux = listaacao->primeiro->prox;
		aux1 = listaposterior->primeiro->prox->prox;
		listaacao->primeiro->prox = listaposterior->primeiro->prox;
		listaacao->primeiro->prox->prox = aux;
		listaposterior->primeiro->prox = aux1;
	}
}

void insereacao(tipolista *lista,tipolista *listaacao){
	//insere um elemento na lista de acoes do elevador
	apontador aux = listaacao->primeiro->prox;
	listaacao->primeiro->prox = lista->primeiro->prox;
	lista->primeiro->prox = lista->primeiro->prox->prox;
	listaacao->primeiro->prox->prox = aux;
}

void ordena_crescente(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior){
	//ordena a lista de acoes de forma crescente a partir do andar atual do elevador.
	//Caso a chamada ou o destino sejam abaixo do andar atual, essa acao eh mandada para a lista
	//posterior de acoes do elevador
	int saiu=0;
	apontador aux, anterior;
	while (saiu==0){
		aux = listaacao->primeiro->prox;
		anterior = listaacao->primeiro;
     	saiu=1;
		while ((aux != NULL) && (aux->prox != NULL)){
			if (aux->andar_dest < elevador->andar_atual){
				anterior->prox = aux->prox;
				insere_listaposterior(listaposterior, aux);
				aux=anterior->prox;
			}
			else{
				if (aux->andar_dest > aux->prox->andar_dest){
					anterior->prox = aux->prox;
		           	aux->prox = anterior->prox->prox;
		           	anterior->prox->prox = aux;
		           	anterior = anterior->prox;
		           	saiu=0;
				}
				else{
				    aux=aux->prox;
				    anterior = anterior->prox;
				}	
			}

	    }
		if ((listaacao->primeiro->prox != NULL)&&(listaacao->primeiro->prox->prox == NULL)){
			if(listaacao->primeiro->prox->andar_dest < elevador->andar_atual){
				insere_listaposterior(listaposterior, listaacao->primeiro->prox);
				listaacao->primeiro->prox = NULL;
			}	
		}
	}
}

void ordena_decrescente(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior){
	//igual a funcao "ordena_crescente", so que ao contrario, priorizando as acoes abaixo do andar
	//atual do elevador
	int saiu=0;
	apontador aux, anterior;
	while (saiu==0){
		aux = listaacao->primeiro->prox;
		anterior = listaacao->primeiro;
     	saiu=1;
     	while ((aux != NULL) && (aux->prox != NULL)){
     		if (aux->andar_dest > elevador->andar_atual){
				anterior->prox = aux->prox;
				insere_listaposterior(listaposterior, aux);
				aux=anterior->prox;
				
				
			}
			else{
				if (aux->andar_dest < aux->prox->andar_dest){
					anterior->prox = aux->prox;
		           	aux->prox = anterior->prox->prox;
		           	anterior->prox->prox = aux;
		           	anterior = anterior->prox;
		           	saiu=0;
				}
				else{
				    aux = aux->prox;
				    anterior = anterior->prox;
				}	
			}

	    }
		if ((listaacao->primeiro->prox != NULL)&&(listaacao->primeiro->prox->prox == NULL)){
			if(listaacao->primeiro->prox->andar_dest > elevador->andar_atual){
				insere_listaposterior(listaposterior, listaacao->primeiro->prox);
				listaacao->primeiro->prox = NULL;
			}	
		}
	}
}

void ordena_tempo(tipolista *lista){
	//ordena a lista que recebe os dados de entrada em ordem crescente de tempo de chamada
	int saiu=0;
	apontador aux, anterior;
	while (saiu==0){
		aux = lista->primeiro->prox;
		anterior = lista->primeiro;
     	saiu=1;
		while ((aux->prox != NULL)&&(aux != NULL)){
			if (aux->tempo_chamada > aux->prox->tempo_chamada){
	           	anterior->prox = aux->prox;
	           	aux->prox = anterior->prox->prox;
	           	anterior->prox->prox = aux;
	           	anterior = anterior->prox;
	           	saiu=0;
			}
			else{
				aux=aux->prox;
				anterior = anterior->prox;
			}	
		}

	}
}

apontador libera(apontador anterior, apontador aux1){
	//quando a pessoa sai do elevador, a memoria que ela ocupa no programa eh liberada
	anterior->prox=aux1->prox;
	free(aux1);
	return anterior->prox;
}

void desaloca(tipolista *lista){
	//desaloca as celulas cabeca das listas criadas
	apontador aux, aux1;
	aux = lista->primeiro;
	aux1 = lista->primeiro;
	while (aux != NULL){
		aux1 = aux->prox;
		free(aux);
		aux = aux1;
	}
}