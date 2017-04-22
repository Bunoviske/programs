/*Trabalho 1 (simulador de elevador) - ED TURMA E - PROFESSOR: George Teodoro
Codigo feito por: Bruno Fernandes e Leonardo Nunes*/

 #include "logica.h"

int main(int argc, char **argv) {

//declaracao das variaveis utilizadas
FILE *fp, *fp1;
int *vetor, *vetor2, *vetor3, *vetor4, *vetor5;
tipolista lista;
struct timeval inicio, final;
float tmili, tmili2, tmili3, tmili4, tmili5;
int copias1, comp1, copias2, comp2, copias3, comp3, copias4, comp4, copias5, comp5, opt, q, n, i, semente, cenario;

 /* Variáveis que receberão os argumentos
     das opções. */

    char *entrada=NULL, *saida=NULL, *sem=NULL, *cen=NULL;
    /* getopt() retorna o caractere de uma opção a cada
     * iteração e -1 para marcar o fim do processo. */
    while( (opt = getopt(argc, argv, "c:e:s:n:")) > 0 ) {
        switch ( opt ) {
            case 'c': /* opção -c */
                cen = optarg ;
                break ;
            case 'e': /* opção -e */
                entrada = optarg ;
                break ;
            case 's': /* opção -s */
                saida = optarg ;
                break ;
            case 'n': /* opção -n */
                sem = optarg ;
                break ;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
                return -1 ;
        }
    }
    //todos argumentos devem ser inseridos na linha de comando, senao da erro
    if ((entrada == NULL )||(saida == NULL )||(sem == NULL )||(cen == NULL )){
        mostra_ajuda(argv[0]);
        return 0;
    }
    cenario = atoi(cen);
    semente = atoi(sem);

    //cenario de testes 1
    if(cenario == 1) {
    	fp = fopen(entrada, "r");
  		if(fp == NULL){
  			printf("Arquivo não existe!\n");
  			return 0;
  		}
      limpar_arquivo(&fp1, saida, cenario);
      entrada_arquivo(&fp, &q);
  		for(i=0; i < q; i++){
        //para cada valor de n, as variaveis que armazenam os dados de analise devem ser zerados
  			comp1 = 0;
  			copias1 = 0;
  			comp2 = 0;
  			copias2 = 0;

        entrada_arquivo(&fp, &n);
  			vetor = (int*) malloc(sizeof(int) * n);
  			flvazia(&lista);
        //gera os dados num vetor e numa lista duplamente encadeada
  			gerar1(vetor, n, semente, &lista);

        //ordena o vetor, e com a funcao gettimeofday, pega o tempo necessario para a ordenacao
  			gettimeofday(&inicio, NULL);
  			quicksort_array(0, n-1, vetor, 0, 0, &copias1, &comp1);
  			gettimeofday(&final, NULL);
        tmili = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

        //ordena a lista, e com a funcao gettimeofday, pega o tempo necessario para a ordenacao
        gettimeofday(&inicio, NULL);
  			quicksort_lista(lista.primeiro->prox, lista.ultimo, &copias2, &comp2);
  			gettimeofday(&final, NULL);
  			tmili2 = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

        saida1(&fp1, saida, tmili, tmili2, comp1, comp2, copias1, copias2, n);

        free(vetor);
        libera(&lista);
  		}
  		fclose(fp);
	}
  //cenario de testes 2
	else if (cenario == 2){
		fp = fopen(entrada, "r");
		if(fp == NULL){
			printf("Arquivo não existe!\n");
			return 0;
		}
    limpar_arquivo(&fp1,saida, cenario);
    entrada_arquivo(&fp, &q);
		for(i=0; i < q; i++){
      //para cada valor de n, as variaveis que armazenam os dados de analise devem ser zerados
			comp1 = 0;
			copias1 = 0;
			comp2 = 0;
			copias2 = 0;
			comp3 = 0;
			copias3 = 0;
			comp4 = 0;
			copias4 = 0;
			comp5 = 0;
			copias5 = 0;

      entrada_arquivo(&fp, &n);
      vetor = (int*) malloc(sizeof(int) * n);
			vetor2 = (int*) malloc(sizeof(int) * n);
			vetor3 = (int*) malloc(sizeof(int) * n);
			vetor4 = (int*) malloc(sizeof(int) * n);
			vetor5 = (int*) malloc(sizeof(int) * n);
      //gera os dados em 5 vetores, para serem analisados e ordenados usando variacoes do algoritmo diferentes
			gerar2(vetor, vetor2, vetor3, vetor4, vetor5, n, semente);

      /*abaixo, cada ordenacao e tempo adquirido para fazer isso usa variacoes
      do algoritmo diferentes. Usa-se k=0,k=3, k=5, m=10 e m=100*/

			gettimeofday(&inicio, NULL);
			quicksort_array(0, n-1, vetor, 0, 0, &copias1, &comp1);
			gettimeofday(&final, NULL);
			tmili = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

			gettimeofday(&inicio, NULL);
			quicksort_array(0, n-1, vetor2, 3, 0, &copias2, &comp2);
			gettimeofday(&final, NULL);
			tmili2 = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

			gettimeofday(&inicio, NULL);
			quicksort_array(0, n-1, vetor3, 5, 0, &copias3, &comp3);
			gettimeofday(&final, NULL);
			tmili3 = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

			gettimeofday(&inicio, NULL);
			quicksort_array(0, n-1, vetor4, 0, 10, &copias4, &comp4);
			gettimeofday(&final, NULL);
			tmili4 = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

			gettimeofday(&inicio, NULL);
			quicksort_array(0, n-1, vetor5, 0, 100, &copias5, &comp5);
			gettimeofday(&final, NULL);
			tmili5 = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);

			saida2(&fp1, saida, tmili, tmili2, tmili3, tmili4, tmili5, comp1, comp2, comp3, comp4, comp5, copias1, copias2, copias3, copias4, copias5, n);

      free(vetor);
			free(vetor2);
			free(vetor3);
			free(vetor4);
			free(vetor5);
		}
	}
  else{
    printf("Cenario inválido: somente cenarios 1 ou 2 validos\n");
  }
	return 0;
}
