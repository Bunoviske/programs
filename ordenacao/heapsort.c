#include <stdio.h>


void troca(int index1, int index2, int vetor[]){
  int aux;
  aux = vetor[index1];
  vetor[index1] = vetor[index2];
  vetor[index2] = aux;
}

int heapproperty(int tam, int vetor[]){
  int heap = 1, i=0;
  int aux;

  if ((tam - 1)%2 == 0){ //se for par, chega até 2i + 2
    while((2*i + 2) < tam) {
      if ((vetor[i] < vetor[2*i +1]) || (vetor[i] < vetor[2*i +2])) {
        if (vetor[2*i +2] < vetor[2*i +1]) {
          aux = 2*i+1;
          troca(aux, i, vetor);
          i = 2*i+1;
          heap = 0;
        }
        else{
          aux = 2*i+2;
          troca(aux, i, vetor);
          i = 2*i+2;
          heap = 0;
        }
      }
      else{
        i++;
      }
    }
    return heap;
  }
  else{ // se for impar, chega ate 2i +1
    while((2*i + 1) < tam) {
      if (2*i+1 == tam-1) {
          if (vetor[i] < vetor[2*i +1]) {
            aux = 2*i+1;
            troca(aux, i, vetor);
            i=tam;
            heap = 0;
          }
          else{
            i++;
          }
      }
      else{
        if ((vetor[i] < vetor[2*i +1]) || (vetor[i] < vetor[2*i +2])) {
          if (vetor[2*i +2] < vetor[2*i +1]) {
            aux = 2*i+1;
            troca(aux, i, vetor);
            i = 2*i+1;
            heap = 0;
          }
          else{
            aux = 2*i+2;
            troca(aux, i,vetor);
            i = 2*i+2;
            heap = 0;
          }
        }
        else{
          i++;
        }
      }
    }
    return heap;
  }
}

void ordena(int tam, int vetor[]){
    int tam_liq = tam;
    while (tam_liq > 1) {
      troca(0, tam_liq-1, vetor);
      tam_liq--;
      heapproperty(tam_liq, vetor);
    }
}



int main(){
  int tam =4;
  int vetor[tam];
  int i;

  for ( i = 0; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
  }
  while (heapproperty(tam, vetor) == 0){
  }
  ordena(tam, vetor);
  for (i=0; i<tam; i++) {
    printf("%d\n", vetor[i]);
  }

  return 0;
}
