#include "logica.h"

void define_direcao(tipoelevador *elevador, apontador aux){
	//funcao responsavel por definir a direcao do elevador, caso ele nao tenha uma
	int aux1;
	aux1 = (elevador->andar_atual) - aux->andar_chamada;
		if (aux1 > 0){
			elevador->direcao = 'b';
		}
		else {
			if(aux1 < 0){
				elevador->direcao = 'c';
			}
		    else{
				aux1 = elevador->andar_atual - aux->andar_destino;
				if (aux1 > 0){
					elevador->direcao = 'b';
				}

				else
				{
					elevador->direcao = 'c';
				}
			}
		}

}

void organiza_listaacao(tipoelevador *elevador, tipolista *lista,tipolista *listaacao, tipolista *listaposterior, char ent_ou_saida){
	//funcao que organiza a lista de acoes do elevador, conforme a direcao deste
	if (ent_ou_saida == 'e'){
		insereacao(lista,listaacao);
		listaacao->primeiro->prox->andar_dest =listaacao->primeiro->prox->andar_chamada;

	}
    else{
		if(ent_ou_saida == 's'){
    		listaacao->primeiro->prox->andar_dest = listaacao->primeiro->prox->andar_destino;
    	}
    }

    if (elevador->direcao == 'c'){
    	ordena_crescente(elevador, listaacao, listaposterior);
	}
	else {
		if (elevador->direcao == 'b'){
			ordena_decrescente(elevador, listaacao, listaposterior);
		}
	}
}

void chamada(tipolista *lista, tipolista *listaacao, tipolista *listaposterior, int *zepslon, tipoelevador *elevador){
		//funcao que verifica se houve alguma chamada em um determinado tempo zepslon. caso tenha alguma,
		//chama-se a funcao para organizar novamente a lista de acoes do elevador
		apontador aux;
		aux = lista->primeiro->prox;
		if ((aux != NULL) && (*zepslon == aux->tempo_chamada)) {
			if (elevador->direcao == 'n'){
				define_direcao(elevador, aux);
		    }
			aux = aux->prox;
			organiza_listaacao(elevador, lista,listaacao, listaposterior,'e');
			while((aux != NULL) && (*zepslon == aux->tempo_chamada)){
				aux=aux->prox;
				organiza_listaacao(elevador, lista,listaacao, listaposterior,'e');
			}

		}
}

void verifica_andar(tipolista *lista, tipolista *listaacao, tipoelevador *elevador, tipolista *listaposterior, FILE *fp, int *zepslon){
	//funcao que verifica se o andar atual do elevador eh o andar de destino ou de chamada da primeira pessoa da lista
	//de acoes do elevador. Caso seja, eh priorizado a saida das pessoas do elevador, para depois entrarem as pessoas que
	//chamaram ele nesse andar. Tambem eh testado se o elevador esta lotado
	int lotado = 0;
	apontador anterior,aux1, aux = listaacao->primeiro->prox;
	anterior = listaacao->primeiro;
	if ((aux != NULL) && (elevador->andar_atual == aux->andar_dest)){
			aux1 = aux;
			while ((aux1 != NULL) && (elevador->andar_atual == aux1->andar_dest)){
				if (aux1->andar_dest == aux1->andar_destino){
					aux1->tempo_saida = (*zepslon) - 1;
					saida(fp, aux1);
					aux1 = libera(anterior, aux1);
					elevador->cap_atual--;
					lotado = -50000;
				}
				else{
					aux1=aux1->prox;
					anterior=anterior->prox;
				}
			}
			aux = listaacao->primeiro->prox;
			while ((aux != NULL) && (elevador->andar_atual == aux->andar_dest)){
				if(elevador->cap_atual == elevador->cap_max) {
					listaacao->primeiro->prox = listaacao->primeiro->prox->prox;
					insere_listaposterior(listaposterior, aux);
					aux = listaacao->primeiro->prox;
					lotado++;
			    }
		        else{
		        	organiza_listaacao(elevador, lista,listaacao, listaposterior,'s');
	        		elevador->cap_atual++;
	        		aux->tempo_entrada = *zepslon;
	        		aux = listaacao->primeiro->prox;
	        		lotado = -50000;
	        	}
			}
		if (lotado < 0){
			(*zepslon) = (*zepslon) + 1;
			chamada(lista, listaacao, listaposterior, zepslon, elevador);
		}


	}
}


void move_elevador(tipoelevador *elevador){
	//funcao que incrementa ou decrementa o andar atual do elevador conforme sua direcao
	if (elevador->direcao == 'c'){
        elevador->andar_atual++;
    }
    else if (elevador->direcao == 'b'){
        elevador->andar_atual--;

    }

}
void verifica_direcao(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior, tipolista *lista, int *simulacao, int *muda_andar){
	//funcao que verifica se o elevador trocou de direcao. Alem disso, verifica se a simulacao terminou
	if (listaacao->primeiro->prox == NULL){
		if (listaposterior->primeiro->prox == NULL){
				if (lista->primeiro->prox == NULL){
					*simulacao = 0;
					elevador->direcao = 'n';
				}
			    else{
					elevador->direcao = 'n';
				}
		}
		else{
			if (elevador->direcao == 'c'){
				elevador->direcao = 'b';
				transforma_lista(listaacao, listaposterior);
				move_elevador(elevador);
				*muda_andar = 1;
				ordena_decrescente(elevador, listaacao, listaposterior);
			}
			else{
				if (elevador->direcao == 'b')
				{
					elevador->direcao = 'c';
					transforma_lista(listaacao, listaposterior);
					move_elevador(elevador);
					*muda_andar = 1;
					ordena_crescente(elevador, listaacao, listaposterior);
				}
			}
		}
	}
}
