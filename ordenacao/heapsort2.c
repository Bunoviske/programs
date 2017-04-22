#include <stdio.h>


void troca(int index1, int index2, int vetor[]){
  int aux;
  aux = vetor[index1];
  vetor[index1] = vetor[index2];
  vetor[index2] = aux;
}

void heapproperty(int tam, int vetor[]){
  int f, i;
  for (i = 1; i < tam; i++) {
    f = i + 1;
    while (f > 1 && vetor[f - 1] > vetor[f/2 - 1]) {
      troca(f - 1, f/2 - 1, vetor);
      f /= 2;
     }
   }
}

void insere_novo(int tam, int vetor[]){
int f = tam;
  while (f > 1 && vetor[f - 1] > vetor [f/2 -1]) {
    troca(f - 1, f/2 - 1,vetor);
    f /= 2;
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
  int tam = 5;
  int vetor[tam];
  int i;
  char c;
  for ( i = 0; i < 4; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
  }
  heapproperty(4, vetor);
  ordena(4, vetor);
  int continua =1 ;
  while(continua == 1){
    getchar();
    printf("Continuar?");
    scanf("%c", &c);
    getchar();
    if (c == 's') {
      printf("digite um valor: ");
      scanf("%d", &vetor[i]);
      insere_novo(tam, vetor);
      ordena(tam, vetor);
    }
    continua = 0;

  }
  for (i=0; i< tam; i++) {
    printf("%d\n", vetor[i]);
  }

  return 0;
}
