#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//quantidade de neuronios de entrada (binario + bias)
#define entrada 3
//quantidade de neuronios de saida
#define saida 2
//quantidade de entradas
#define in 4
//quantidade de bits que representam a entrada
#define binario 2

int main(){
  /*primeiro armazena-se as dados de entrada em "entradas" e a saida esperada na matriz "saidas".
  Depois faz a soma ponderada dos pesos e da entrada e a coloca na funcao de transferencia. Logo depois
  os pesos sao ajustados para uma determinada entrada, e o ciclo continua ate que o aprendizado seja concluido
  */

  //ni é a funcao de ativacao
  float w[entrada][saida], err, erro[saida], ni[saida], errom, bias, aprend, entradas[in][binario];
  float saidas[in][saida], phi[saida];
  int x, cont, contt, contin = 0, epocas, testeerro=0, funcao;
  char continua = 's';

//inicializa os pesos iguais a zero
  for (x = 0; x < entrada; x++) {
    for (cont = 0; cont < saida; cont++) {
      w[x][cont]=0;
    }
  }

  printf("Entre com o valor do bias, taxa de aprendizagem, numero de iteracoes, valor do erro esperado e a funcao desejada[degrau(1) ou sigmoide(2)]\n");
  scanf("%f", &bias);
  scanf("%f", &aprend);
  scanf("%d", &epocas);
  scanf("%f", &err);
  scanf("%d", &funcao);

  printf("Entre com os dados de entrada e de saida para o treinamento\n");
  for (x =0; x< in;x++){
    for (cont = 0; cont < binario; cont++) {
      printf("Entrada %d, Neuronio de entrada %d:", x+1, cont+1);
//matriz que representa a tabela de entrada desejada
      scanf("%f", &entradas[x][cont]);
    }
  }

  for (x =0; x< in;x++){
    for (cont = 0; cont < saida; cont++) {
      printf("Saida %d, Neuronio de saida %d:", x+1, cont+1);
//matriz que representa a tabela de saida desejada
      scanf("%f", &saidas[x][cont]);
    }
  }

  printf("Todos os pesos iniciados com zero e iniciando processo iterativo\n");
  cont = 0;
  while ((cont < epocas) && (testeerro == 0) && (continua != 'n')) {
    cont++;
    printf("Iteraçao %d:\n", cont);
    //entrada - 1 por causa do bias
    for (x = 0; x < binario; x++) {
      printf("Entradas: %.2f ", entradas[contin][x]);
    }
    printf("\n");
    for (x = 0; x < saida; x++) {
      //existe um valor da funcao de ativacao para cada neuronio de saida (x)
      ni[x] = w[0][x]*bias;
      for (contt = 0; contt < binario; contt++) {
        ni[x] = ni[x] + w[contt+1][x] * entradas[contin][contt];
      }
      switch (funcao) {
        case 1:
          if (ni[x] > 0) {
            phi[x] = 1;
          }
          else{
            phi[x]=0;
          }
          break;
        case 2:
          phi[x] = 1 / (1 + exp(-ni[x]));
          break;
      }
      erro[x] = saidas[contin][x] - phi[x];
      printf("Saida esperada:%.2f\n", saidas[contin][x]);
      printf("Saida da rede:%.2f\n", phi[x]);
    }
    errom = 0;
    for (x = 0; x < saida; x++) {
      errom += erro[x]/saida;
    }
    printf("Erro medio geral: %.2f\n", errom);
    if (abs(errom) < err) {
      testeerro = 1;
    }
    else{
      testeerro = 0;
    }
    printf("Corrigindo pesos...\n");
    for (x = 0; x < entrada; x++) {
      for (contt = 0; contt < saida; contt++) {
        if (x == 0) {
          //primeira linha da matriz de pesos corresponde ao bias
          w[x][contt] += aprend*erro[contt]*bias;
        }
        else{
          w[x][contt] += aprend*erro[contt]*entradas[contin][x-1];
        }
      }
    }
    for (x = 0; x < entrada; x++) {
      for (contt = 0; contt < saida; contt++) {
        printf("w[%d][%d]: %.2f\n", x+1, contt+1  , w[x][contt]);
      }
    }
    printf("Continua?");
    scanf("%c", &continua);
    contin++;
    if (contin > entrada) {
      contin = 0;
    }
  }
  printf("Finalizado\n");
  return 0;
}
