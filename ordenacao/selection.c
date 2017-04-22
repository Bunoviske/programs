#include <stdio.h>

int main(){
  int tam = 10;
  int vetor[tam];
  int aux,j, i, menor;
  for ( i = 0; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
    getchar();
  }
  for (i=0; i<(tam-1); i++){
    menor = i;
    for (j=i+1;j<tam;j++){
      if (vetor[j]< vetor[menor]) {
        menor = j;
      }
    }
    aux = vetor[menor];
    vetor[menor] = vetor[i];
    vetor[i] = aux;
  }
  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
