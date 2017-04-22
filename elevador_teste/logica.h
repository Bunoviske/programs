#include "in_out.h"

void verifica_andar(tipolista *lista, tipolista *listaacao, tipoelevador *elevador, tipolista *listaposterior, FILE *fp, int *zepslon);
void define_direcao(tipoelevador *elevador, apontador aux);
void chamada(tipolista *lista, tipolista *listaacao, tipolista *listaposterior, int *zepslon, tipoelevador *elevador);
void organiza_listaacao(tipoelevador *elevador, tipolista *lista, tipolista *listaacao, tipolista *listaposterior, char ent_ou_saida);
void move_elevador(tipoelevador *elevador);
void verifica_direcao(tipoelevador *elevador, tipolista *listaacao, tipolista *listaposterior, tipolista *lista, int *simulacao, int *muda_andar);
