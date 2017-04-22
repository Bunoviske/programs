#include "in_out.h"

void mostra_ajuda(char *name) {
    fprintf(stderr, "\
            [uso]%s <opcoes>\n\
            -e Nome do arquivo de entrada   Nome do arquivo onde serao lidas as entradas.\n\
            -i Cidade de origem   Numero que representa a cidade na qual será o ponto de partida.\n", name) ;
    printf("\n\n             DIGITE OS DOIS ARGUMENTOS PARA INICIAR O PROGRAMA\n\n\n");

    exit(-1) ;
}

void saida(tipolista *lista_aux) {
  //funcao que imprime a saida do resultado para o usuario
	apontador aux = lista_aux->primeiro->prox;

	if(aux == NULL){
		printf("Nao existe caminho que conecte todas as cidades sem passar 2 vezes em uma mesma cidade.\n");
	}
	else {
		printf("A distancia total e %d\n", lista_aux->soma);
		printf("%d <- ", aux->destino);
		while(aux != NULL){
			if(aux->prox == NULL) {
				printf("%d.\n", aux->origem);
			}
			else {
				printf("%d <- ", aux->origem);
			}
			aux = aux->prox;
		}
		aux = lista_aux->primeiro->prox;
		while(aux != NULL){
			printf("A distancia entre %d e %d e : %d\n", aux->origem, aux->destino, aux->peso);
			aux = aux->prox;
		}
	}
}

void le_cidades(FILE **fp, int *qnt){
  //leitura da quantidade de cidades
  fscanf(*fp, "%d\n", qnt);
}

int le_arestas(FILE **fp,int *i, int *x, int* p){
  //leitura dos caminhos entre as cidades
  return fscanf(*fp, "%d %d %d\n", i, x, p);
}
