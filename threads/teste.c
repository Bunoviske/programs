#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// compilar com -lpthread

pthread_mutex_t meu_mutex;

typedef struct{
  int id;

}estrutura;

void * thread(void* arg){

  estrutura *aux =  (estrutura *) arg;
  pthread_mutex_lock(&meu_mutex);
  printf("%d\n", aux->id);
  pthread_mutex_unlock(&meu_mutex);
  free(aux);
}

int main(int argc, char const *argv[]) {

  pthread_t t[5];
  int i;
  estrutura *socket;
  //pthread_mutex_init(&meu_mutex, NULL);
  for (i = 0; i < 5; i++) {
    socket = (estrutura *) malloc(sizeof(estrutura));
    socket->id = i;
    pthread_create(&t[i], NULL, thread, (void*) (socket));

  }
  while(1);
  pthread_mutex_destroy(&meu_mutex);

  return 0;
}
