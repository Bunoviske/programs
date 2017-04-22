#include <stdio.h>


void merge(int vetor[], int meio,int inicio, int final){
  int k=0, i = inicio, j = meio+1, aux[(final-inicio)+1];

  while ((i <= meio) && (j<=final)) {
    if (vetor[i] > vetor[j]) {
      aux[k] = vetor[j];
      j++;
      k++;
    }
    else{
      aux[k] = vetor[i];
      i++;
      k++;
    }
  }
  if (j>final){
    while (i <= meio) {
      aux[k] = vetor[i];
      k++;
      i++;
    }
  }
  else{
    while (j <= final){
      aux[k] = vetor[j];
      k++;
      j++;
    }
  }
  k=0;
  for (i = inicio; i <= final; i++) {
    vetor[i] = aux[k];
    k++;
  }
}



void mergesort(int vetor[], int inicio, int final){
  int meio, aux1;
  meio = (inicio + final)/2;
  if ((final - inicio) > 1) {
    mergesort(vetor, inicio, meio);
    mergesort(vetor, meio+1, final);
    merge(vetor, meio, inicio, final);
  }
  else{
    if (vetor[inicio] > vetor[final]){
      aux1 = vetor[inicio];
      vetor[inicio] = vetor[final];
      vetor[final] = aux1;
      return;
    }
    else{
      return;
    }
  }
}

int main(){
  int tam = 5;
  int vetor[tam];
  int i,j;

  for ( i = 0; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);

  }
  mergesort(vetor, 0, tam-1);

  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
