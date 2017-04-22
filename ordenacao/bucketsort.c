#include <stdio.h>

typedef struct {
  int topo;
  int balde[5];
}bucket;


void insertion(int vetor[], int tam){
  int i, j, aux;
  for (i=1; i<tam; i++){
    aux = vetor[i];
    for (j=i;vetor[j-1] > aux && j>0; j--){
      vetor[j] = vetor[j-1];
    }
    vetor[j] = aux;
  }

}


void bucketsort(int vetor[], int tam, int maior){
  int i, aux, j, k;
  bucket b[5];
  float intervalo = (maior/5);
  float inicio, final;
  for (i = 0; i < tam; i++) {
    b[i].topo = 0;
  }
  for (i = 0; i < tam; i++) {
      inicio = 0;
      final = intervalo;
      while (final <= maior) {
        if ((vetor[i] > inicio)&&(vetor[i] <= final)) {
          aux = (int)(inicio/intervalo);
          b[aux].balde[b[aux].topo] = vetor[i];
          b[aux].topo ++;
        }
        inicio = final;
        final += intervalo;
  }
  for (i = 0; i < tam; i++) {
    insertion(b[i].balde, b[i].topo);
  }
  k=0;
  for (i = 0; i < 5; i++) {
    for (j=0; j < b[i].topo; j++) {
      vetor[k] = b[i].balde[j];
      k++;
    }
  }
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
  bucketsort(vetor, tam, maior);
  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
