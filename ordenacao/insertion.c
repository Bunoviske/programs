#include <stdio.h>

int main(){
  int vetor[10];
  int aux,i,j;
  for ( i = 0; i < 10; i++) {
    printf("digite um valor: \n");
    scanf("%d\n", &vetor[i]);
  }
  for (i=1; i<10; i++){
    aux = vetor[i];
    for (j=i;vetor[j-1] > aux && j>0; j--){
      vetor[j] = vetor[j-1];
    }
    vetor[j] = aux;
  }
  for (j=0; j<10; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
