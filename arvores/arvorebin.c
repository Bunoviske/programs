#include <stdio.h>
#include <stdlib.h>


typedef struct tipocelula * apontador;

typedef struct tipocelula{
   int elemento;
   apontador dir, esq;
 }celula;

void favazia(apontador *raiz){
	(*raiz)->dir = NULL;
	(*raiz)->esq = NULL;
}

void insere(apontador *raiz, int x){
	//insere um elemento na arvore
		if ((*raiz) != NULL){
      if (x > (*raiz)->elemento) {
        insere(&(*raiz)->dir, x);
      }
      else{
        insere(&(*raiz)->esq, x);
      }
    }
    else{
      *raiz = (apontador) malloc(sizeof(celula));
      (*raiz)->elemento = x;
      favazia(raiz);
    }
}

void remocao(apontador *raiz){
  if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)) {
    free(*raiz);
  }
  else{
    if ((*raiz)->esq == NULL) {
      apontador aux;
      aux = (*raiz);
      *raiz = (*raiz)->dir;
      free(aux);
    }
    else{
      if ((*raiz)->dir == NULL){
        apontador aux;
        aux = (*raiz);
        *raiz = (*raiz)->esq;
        free(aux);
      }
      else{
        apontador anterior = *raiz , aux = (*raiz)->dir;
        apontador esquerda = (*raiz)->esq;
        apontador direita = (*raiz)->dir;
        while (aux->esq != NULL){
          anterior = aux;
          aux = aux->esq;
        }
        apontador aux1 = *raiz;
        *raiz = aux;
        if (anterior != *raiz){
          (*raiz)->dir = direita;
          (*raiz)->esq = esquerda;
          anterior->esq = aux->dir;
        }
        free(aux1);
      }
    }
  }
}

int procura_remocao(apontador *raiz, int x){
  if ((*raiz) != NULL){
    if (x == (*raiz)->elemento) {
      remocao(raiz);
      return 0;
    }
    else{
      if (x > (*raiz)->elemento) {
        return procura_remocao(&(*raiz)->dir, x);
      }
      else{
        return procura_remocao(&(*raiz)->esq, x);
      }
    }
  }
  else{
    return -1;
  }
}

void libera(apontador *raiz){
	//libera os elementos da arvore (pos-ordem)
	if ((*raiz) != NULL) {
		libera(&(*raiz)->esq);
    libera(&(*raiz)->dir);
    free(*raiz);
	}
}

void emordem(apontador *raiz){
  if ((*raiz) != NULL) {
		emordem(&(*raiz)->esq);
    printf("%d\n", (*raiz)->elemento);
    emordem(&(*raiz)->dir);
	}
}

int main() {
  int i, aux;
  apontador raiz = (apontador) malloc(sizeof(celula));
  favazia(&raiz);
  printf("digite um valor: \n");
  scanf("%d", &aux);
  raiz->elemento = aux;
  for ( i = 1; i < 5; i++) {
    printf("digite um valor: \n");
    scanf("%d", &aux);
    insere(&raiz, aux);
  }

  //PARTE DE REMOCAO COM PROBLEMAS
  if (procura_remocao(&raiz, aux) == -1){
    printf("numero invalido para remocao\n" );
  }
  else{
    printf("numero removido %d\n", aux);
  }
  
  emordem(&raiz);
  libera(&raiz);
  return 0;

}
