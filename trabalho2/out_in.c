#include "out_in.h"

void mostra_ajuda(char *name) {
  //mostra o menu de ajuda para o usuario executar o programa corretamente
    fprintf(stderr, "\
            [uso]%s <opcoes>\n\
            -e Nome do arquivo de entrada   Nome do arquivo onde serao lidas as entradas.\n\
            -s Nome do arquivo de saida     Nome do arquivo onde serao registrados os resultados.\n\
            -n Numero que representa a semente   Numero que gera as entradas aleatorias.\n\
            -c Numero do cenario que deseja utilizar  1 - Impacto de estruturas de dados diferentes. 2 - Impacto das variacoes do QuickSort.\n", name) ;
    printf("\n\n             DIGITE OS QUATRO ARGUMENTOS PARA INICIAR \n\n\n");

    exit(-1) ;
}

void entrada_arquivo(FILE** fp, int* valor){
  //le os parametros do arquivo de entrada escolhido pelo usuario
  fscanf(*fp, "%d\n", valor);
}

void limpar_arquivo(FILE** fp1 ,char saida[], int cenario){
  //limpa o arquivo de saida e mostra qual cenario esta sendo analisado
  *fp1 = fopen(saida, "w");
  fprintf(*fp1, "ANALISE DAS METRICAS NO CENARIO %d\n\n", cenario);
  fclose(*fp1);
}

void saida1(FILE** fp1, char saida[], int tmili, int tmili2, int comp1, int comp2, int copias1, int copias2, int n) {
  //saida das metricas analisados no cenario 1
  *fp1 = fopen(saida, "a");
	fprintf(*fp1, "N = %d \n\n Tempo de ordenacao do vetor: %d ms \n Comparacoes no vetor: %d \n Copias no vetor: %d \n\n Tempo de ordenacao da lista: %d ms \n Comparacoes na lista: %d \n Copias na lista: %d\n\n", n, tmili, comp1, copias1, tmili2, comp2, copias2);
	fclose(*fp1);
}

void saida2(FILE** fp1,char saida[], int tmili, int tmili2, int tmili3, int tmili4, int tmili5, int comp1, int comp2, int comp3, int comp4, int comp5, int copias1, int copias2, int copias3, int copias4, int copias5, int n) {
  //saida das metricas analisados no cenario 2
	*fp1 = fopen(saida, "a");
	fprintf(*fp1, "N = %d \n\n Tempo Quicksort recursivo: %d ms \n Comparacoes Quicksort recursivo: %d \n Copias Quicksort recursivo: %d \n\n Tempo Quicksort/mediana k=3: %d ms \n Comparacoes Quicksort/mediana k=3: %d  \n Copias Quicksort/mediana k=3: %d \n\n Tempo Quicksort/mediana k=5: %d ms \n Comparacoes Quicksort/mediana k=5: %d \n Copias Quicksort/mediana k=5: %d \n\n Tempo Quicksort/Insercao m=10: %d ms \n Comparacoes Quicksort/Insercao m=10: %d \n Copias Quicksort/Insercao m=10: %d \n\n Tempo Quicksort/Insercao m=100: %d ms \n Comparacoes Quicksort Insercao m=100: %d \n Copias Quicksort Insercao m=100: %d\n\n", n, tmili, comp1, copias1, tmili2, comp2, copias2, tmili3, comp3, copias3, tmili4, comp4, copias4, tmili5, comp5, copias5);
	fclose(*fp1);
}
