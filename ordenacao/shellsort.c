#include <stdio.h>
//#include <math.h> // -lm na hora de compilar

int main(){
  int tam = 10;
  int vetor[tam];
  int aux,j, i, gap;
  for ( i = 0; i < tam; i++) {
    printf("digite um valor: ");
    scanf("%d", &vetor[i]);
    getchar();
  }
  //poderia decrementar na forma : (pow(2,k)-1)
  for (gap = tam/2; gap>0; gap = gap/2){
    for (i = gap;  i< tam; i++) {
      aux = vetor[i];
      for (j=i; j >= gap && aux < vetor[j-gap]; j = j - gap) {
        vetor[j]=vetor[j-gap];
      }
      vetor[j]=aux;
    }
  }
  for (j=0; j<tam; j++) {
    printf("%d\n", vetor[j]);
  }

  return 0;
}
