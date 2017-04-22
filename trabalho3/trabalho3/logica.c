  #include "logica.h"

int verifica_vertices(tipolista vetor[], int n){
  //funcao que verifica se todos os vertices foram percorridos em determinado caminho
  int i, flag=0;
  for (i = 0; i < n; i++) {
    if (vetor[i].color == 'b') {
      i = n;
      flag=1;
    }
  }
  if (flag == 1) {
    return 0;
  }
  else{
    return 1;
  }
}


void montar_lista(tipolista *lista_aux,tipolista vetor[], int u){
  /*monta a lista auxiliar que ira armazenar o caminho provisorio se o peso
  total do novo caminho for menor que o atual da lista */
  int aux;

  if (lista_aux->soma == 0) {
    insere_aux(lista_aux, vetor, u, 1);
  }
  else{
    aux = u;
    int somatorio = 0;
    apontador aux1 = vetor[aux].primeiro->prox;

    while (aux != -1) {
      while (aux1 != NULL) {
        if (aux1->destino == vetor[aux].pai) {
          somatorio += aux1->peso;
          break;
        }
        aux1 = aux1->prox;
      }
      aux = vetor[aux].pai;
      aux1= vetor[aux].primeiro->prox;
    }
    if (somatorio < lista_aux->soma){
       insere_aux(lista_aux, vetor, u, 0);
    }
  }
}


void dfs_visit(tipolista *lista_aux,tipolista vetor[], int u, int n){
  /*funcao recursiva que usa recursive backtracking para alcançar todos os vertices 
  com o menor caminho possivel*/
  apontador aux;
  int v, flag =0;

  vetor[u].color = 'c';
  aux = vetor[u].primeiro->prox;

  while(aux != NULL){
    v = aux->destino;
    if (vetor[v].color == 'b'){
      vetor[v].pai = u;
      dfs_visit(lista_aux,vetor, v, n);
      flag =1;
    }
    aux = aux->prox;
  }
  if (flag==0){
    if (verifica_vertices(vetor, n)){
      montar_lista(lista_aux,vetor, u);
    }
  }
  vetor[u].color = 'b';
}
