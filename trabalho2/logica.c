#include "logica.h"

void gerar1(int vetor[], int n, int semente, tipolista* lista) {
	//gera os dados aleatorios para o cenario 1
	int aux, i;

	srand(semente);
	for(i=0; i < n; i++){
		aux = rand()%100000;
		vetor[i] = aux;
		insere(lista, aux);
	}
}

void gerar2(int vetor[], int vetor2[], int vetor3[], int vetor4[], int vetor5[], int n, int semente) {
	//gera os dados aleatorios para o cenario 2
	int aux, i;

	srand(semente);
	for(i=0; i < n; i++){
		aux = rand()%100000;
		vetor[i] = aux;
		vetor2[i] = aux;
		vetor3[i] = aux;
		vetor4[i] = aux;
		vetor5[i] = aux;
	}
}

void insertion_sort(int inicio, int final, int vetor[], int* comp, int* copias){
  //algoritmo de ordenacao Insertion sort
  int i, j, aux;
  for (i = inicio;i<=final; i++){
    aux = vetor[i];
    *copias = *copias + 1;
    for (j=i;vetor[j-1] > aux && j>0; j--){
      *comp = *comp + 1;
      vetor[j] = vetor[j-1];
    }
    vetor[j] = aux;
  }
}

int mediana(int k, int vetor[], int inicio, int final){
	//calculo da mediana para k elementos do vetor

	if(final - inicio + 1 >= k){
    //declaracao das variaveis
    int aux[k], i, j , aux1, aux2, intervalo = (final - inicio + 1)/(k-1);

    i = 0;
    for (j=0; j < k-1; j++){
      aux[j] = vetor[inicio + i];
      i += intervalo;
    }
    aux[j] = vetor[final];
    insertion_sort(0, k-1, aux, &aux1, &aux2);
    i = 0;
    for (j = 0; j < k-1; j++) {
      if (aux[k/2] == vetor[inicio + i]) {
        return (inicio+i);
      }
      i += intervalo;
    }
    return final;
  }
  else{
    return inicio;
  }
}

void quicksort_array(int inicio, int final, int vetor[], int k, int m, int* copias, int* comp){
	//algoritmo de ordenacao quicksort para arranjos
	int too_big_index = inicio;
  int too_small_index = final;
  int pivo;
  if (k==0){
    //se k = 0, optou-se por escolher o pivo na primeira posicao
    pivo = inicio;
  }
  else{
    //se k > 0, escolher o valor mediano para k posicoes do vetor
    pivo = mediana(k, vetor, inicio, final);
  }

  while (too_small_index >= too_big_index){
    while ((vetor[too_big_index] <= vetor[pivo]) && (too_big_index <=final)){
      too_big_index++;
      *comp = *comp + 1;
    }
    while ((vetor[too_small_index] > vetor[pivo]) && (too_small_index >= inicio)){
      too_small_index--;
      *comp = *comp + 1;
    }
    if (too_big_index < too_small_index) {
      troca_array(too_big_index, too_small_index, vetor);
      *copias = *copias + 1;
    }
  }
  if ((final - inicio) > (m-1) ) {
    troca_array(pivo, too_small_index, vetor);
    *copias = *copias + 1;
    quicksort_array(too_small_index + 1, final, vetor, k , m, copias, comp);
    quicksort_array(inicio, too_small_index - 1, vetor, k, m, copias, comp);
  }
  else{
    /*se m=0, o caso se iguala ao caso recursivo visto em sala.
    Nesse caso, o insertion sort fará apenas um teste e acabará.*/

    /*se m > 0, toda vez que o tamanho do subvetor for menor que m,
    o insertion sort fará a ordenação final, otimizando o algoritmo*/

    insertion_sort(inicio, final, vetor, comp, copias);
    return;
  }
}


void quicksort_lista(apontador inicio, apontador final, int* copias, int* comp){
	//algoritmo de ordenacao quicksort para listas duplamente encadeadas

	apontador too_big_index = inicio->prox;
  apontador too_small_index = final;
  apontador pivo = inicio;
  int flag=0;

  if (inicio != final){
    while (flag == 0){
			//flag sera ativada quando o ponteiro too_small ultrapassar o ponteiro too_big

      while ((too_big_index->elemento <= pivo->elemento) && (too_big_index->prox != final->prox)){
        too_big_index = too_big_index->prox;
        *comp = *comp + 1;
      }
      while ((too_small_index->elemento > pivo->elemento) && (too_small_index->ant != inicio->ant)){
        too_small_index = too_small_index->ant;
        *comp = *comp + 1;
        if (verifica_posicao(too_big_index, too_small_index) == 1){
            flag = 1;
          }
      }
      if (flag == 0) {
        troca_lista(&too_big_index, &too_small_index);
        *copias = *copias + 2;
        if (final == too_big_index) {
          final = too_small_index;
        }
      }
      if (too_big_index == too_small_index) {
        flag = 1;
      }
    }
    troca_lista(&pivo, &too_small_index);
    *copias = *copias + 2;
    inicio = pivo;
    if (final == pivo){
      final = too_small_index;
    }
		// chamadas da funcao recursiva, quando ainda existir mais de um elemento para ser ordenado
    if (inicio->ant != too_small_index->ant) {
      quicksort_lista(inicio, too_small_index->ant, copias, comp);
    }
    if (final->prox != too_small_index->prox){
      quicksort_lista(too_small_index->prox , final, copias, comp);
    }
  }
  else{
    return;
  }
}
