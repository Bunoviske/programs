#include <stdio.h>
#include <stdlib.h>


typedef struct tipocelula *apontador;

typedef struct tipocelula{
   int adjacente, peso;
   apontador prox;
 }celula;

 typedef struct{
  char color;
  int pai, dist;
 	apontador primeiro, ultimo;
 }tipolista;


void insere(tipolista vetor[], int i, int x){
  vetor[i].ultimo->prox = (apontador) malloc(sizeof(celula));
  vetor[i].ultimo = vetor[i].ultimo->prox;
  vetor[i].ultimo->adjacente = x;
  vetor[i].ultimo->prox = NULL;
}

void libera(tipolista vetor[], int n){
  int i;
  apontador aux, aux1;
  for (i=0;i<n;i++){
    aux = vetor[i].primeiro;
    while (aux != NULL) {
      aux1 = aux->prox;
      free(aux);
      aux = aux1;
    }
  }
}

void flvazia(tipolista *lista){
	//cria uma lista de ponteiros vazia
	lista->primeiro = (apontador) malloc(sizeof(celula));
	lista->ultimo = lista->primeiro;
	lista->primeiro->prox = NULL;

}

/**********************************
BFS
*****************************************/

void fila(tipolista *fila, int v){
    fila->ultimo->prox = (apontador) malloc(sizeof(celula));
    fila->ultimo = fila->ultimo->prox;
    fila->ultimo->adjacente = v;
    fila->ultimo->prox = NULL;
}

int retira(tipolista *fila){
  int aux;
  apontador aux1;
  if (fila->primeiro->prox != NULL) {
    aux = fila->primeiro->prox->adjacente;
    aux1 = fila->primeiro->prox->prox;
    free(fila->primeiro->prox);
    fila->primeiro->prox = aux1;
    return aux;
  }
  else{
    return -1;
  }

}

void bfs(tipolista vetor[], int n, int vertice_ini){
  tipolista queue;
  apontador aux;
  int v, u = vertice_ini;

  flvazia(&queue);
  vetor[u-1].dist = 0;

  while (u > 0) {
    aux = vetor[u-1].primeiro->prox;
    while(aux != NULL){
      v = aux->adjacente;
      aux = aux->prox;
      if (vetor[v-1].color == 'b'){
        vetor[v-1].color = 'c';
        vetor[v-1].dist = vetor[u-1].dist + 1;
        vetor[v-1].pai = u;
        fila(&queue, v);
      }
    }
    vetor[u-1].color = 'p';
    u = retira(&queue);

  }
}

/**********************************
DFS
*****************************************/

int verifica_vertices(tipolista vetor[], int n){
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

void montar_lista(tipolista vetor[]){

}


void dfs_visit(tipolista vetor[], int u, int n){
  apontador aux;
  int v, flag =0;

  vetor[u].color = 'c';
  aux = vetor[u].primeiro->prox;

  while(aux != NULL){
    v = aux->adjacente;
    if (vetor[v].color == 'b'){
      vetor[u].filho = aux;
      dfs_visit(vetor, v);
      flag =1;
    }
    aux = aux->prox;
  }
  if (flag==0){
    if (verifica_vertices(vetor, n)){
      montar_lista();
    }
  }
  vetor[v].color == 'b';

}

void dfs(tipolista vetor[], int n, int origem){
  //como desce ate o ultimo vertice, se um deles apontar para um cinza,
  //é garantido que tem um loop no grafo. já o bfs nao garante, pois o
  //vertice dentro de um loop pode ficar preto (fazer o teste)

  int time = 0, i;

  dfs_visit(vetor, origem);

  /*
  //loop que passa por todos os vertices a partir de um vertice inicial escolhido
  for ( i = 0; i < n; i++) {
    if (vetor[i].color == 'b'){
      dfs_visit(vetor, i);
    }
  }*/
}



int main() {
  int i,x,n,p=0;
  printf("digite a quantidade de vertices: \n");
  scanf("%d", &n);
  tipolista vetor[n];
  for ( i = 0; i < n; i++) {
    //funcao flvazia
    vetor[i].primeiro = (apontador) malloc(sizeof(celula));
    vetor[i].primeiro->prox = NULL;
    vetor[i].color = 'b';
    vetor[i].dist = -1;
    vetor[i].ultimo = vetor[i].primeiro;
  }

  char c = 's';
  while (c == 's') {
    printf("digite a aresta (u,v)\n");
    scanf("%d", &i);
    scanf("%d", &x);
    insere(vetor, i, x);
    printf("deseja continuar? \n");
    getchar();
    scanf("%c", &c);
  }
  bfs(vetor, n, 1);
  //dfs(vetor, n)
  libera(vetor, n);
  return 0;

}
