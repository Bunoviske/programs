#include <stdio.h>

void countingsort(int A[], int B[],int k,int tam){
  int i, C[k+1];

  for (i = 0; i <= k; i++) {
    C[i]=0;
  }
  for (i = 0; i < tam ; i++) {
    C[A[i]]++;
  }
  /*for (i = 1; i <= k; i++) {
    C[i] += C[i-1];
  }
  for (i = tam-1; i >= 0; i--) {
    B[C[A[i]]-1] = A[i];
    C[A[i]]--;
  }*/
  int j=0;
  i=0;
  while (j <= k) {
    while (C[j] > 0) {
      A[i] = j;
      C[j]--;
      i++;
    }
    j++;
  }


}




int main(){
  int tam = 10;
  int vetor[tam], B[tam];

  // o vetor inicial deve comecar em 1, pois soma-se
  //a quantidade de numeros antes de determinado numero em C[], ou seja,
  //a ultima posicao terá o tamanho do vetor e se considerar comecando em zero da errado

  //outra alternativa é decrementar 1 de cada posicao do histograma dps da soma dos valores
  //nao pode decrementar antes pq senao perde a quantidade de vezes q um valor aparece no
  //vetor de entrada

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
  countingsort(vetor, B, maior, tam);
  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
