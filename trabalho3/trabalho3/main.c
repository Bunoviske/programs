/*Trabalho 3 - ED TURMA E - PROFESSOR: George Teodoro
Codigo feito por: Bruno Fernandes e Leonardo Nunes*/

#include "logica.h"

int main(int argc, char **argv){

int opt, inicio, qnt, i, x, p, s;
FILE *fp;
tipolista lista_aux;

/* Variáveis que receberão os argumentos
     das opções. */
    char *entrada=NULL, *ini=NULL;
    /* getopt() retorna o caractere de uma opção a cada
     * iteração e -1 para marcar o fim do processo. */
    while( (opt = getopt(argc, argv, "e:i:")) > 0 ) {
        switch ( opt ) {
            case 'e': /* opção -e */
                entrada = optarg ;
                break ;
            case 'i': /* opção -i */
                ini = optarg ;
                break ;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
                return -1 ;
        }
    }
    //todos argumentos devem ser inseridos na linha de comando, senao da erro
    if ((entrada == NULL )||(ini == NULL )){
        mostra_ajuda(argv[0]);
        return 0;
    }
    inicio = atoi(ini);
    fp = fopen(entrada, "r");
  	if(fp == NULL){
  		printf("Arquivo não existe!\n");
  		return 0;
  	}

    le_cidades(&fp, &qnt);

    //declaracao de um vetor contendo a quantidade de vertices
 	  tipolista vetor[qnt];

  	for ( i = 0; i < qnt; i++) {
    //funcao faz vetor vazio
    fvvazio(vetor,i);
  	}

 	  while(le_arestas(&fp, &i, &x, &p) > 0) {
      //insere a aresta na lista adjacente dos dois vertices que a conectam
  	  insere(vetor, i, x,p);
      insere(vetor, x, i,p);
  	}

    //define o vertice de origem do caminho
    s = inicio;
  	vetor[s].pai= -1;

    flvazia(&lista_aux);
  	dfs_visit(&lista_aux, vetor, s , qnt);
  	saida(&lista_aux);
  	libera(vetor, qnt);
  	libera_aux(&lista_aux);

  	return 0;

}
