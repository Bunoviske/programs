#include <stdio.h>

void troca(int index1, int index2, int vetor[]){
  int aux;
  aux = vetor[index1];
  vetor[index1] = vetor[index2];
  vetor[index2] = aux;
}

void quicksort(int inicio, int final, int vetor[]){
  int too_big_index = inicio + 1;
  int too_small_index = final;
  int pivo = inicio;

  while (too_small_index >= too_big_index){
    while ((vetor[too_big_index] <= vetor[pivo]) && (too_big_index <=final)){
      too_big_index++;
    }
    while ((vetor[too_small_index] > vetor[pivo]) && (too_small_index >= inicio)){
      too_small_index--;
    }
    if (too_big_index < too_small_index) {
      troca(too_big_index, too_small_index, vetor);
    }
  }
  if( final >= inicio){
    troca(pivo, too_small_index, vetor);
    quicksort(too_small_index + 1, final, vetor);
    quicksort(inicio, too_small_index - 1, vetor);
  }
  else{
    return;
  }
}




int main(){
  int tam = 3;
  int vetor[tam];
  int j, i;
  for ( i = 0; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
    getchar();
  }
  quicksort(0, tam-1, vetor);
  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
