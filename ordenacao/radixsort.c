#include <stdio.h>


void radixsort(int vetor[], int tam, int maior){
  int i, digitosig = 1, C[10];
  int  aux[tam], x;
  while((maior/digitosig) > 0 ){
    for (i = 0; i <= 9; i++) {
      C[i]=0;
    }
    for (i = 0; i < tam; i++) {
      C[((vetor[i]/digitosig) % 10)]++;
    }
    for (i = 1; i <= 9; i++) {
      C[i] += C[i-1];
    }
    for (i = tam-1; i >= 0; i--) {
      x = (vetor[i]/digitosig);
      aux[C[x % 10]-1] = vetor[i];
      C[x % 10]--;
    }
    for ( i = 0; i < tam; i++) {
      vetor[i] = aux[i];
    }
    digitosig *= 10;
  }
}



int main(){
  int tam = 5;
  int vetor[tam];
  int maior,i,j;

  printf("digite um valor: ");
  scanf("%d", &vetor[0]);
  maior = vetor[0];

  for ( i = 1; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
    if (vetor[i] > maior){
      maior = vetor[i];
    }
  }

  radixsort(vetor, tam, maior);

  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
