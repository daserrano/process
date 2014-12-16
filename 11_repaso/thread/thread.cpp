#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

struct TArgumento
{
  int valor;
};

void *pinta(void *arg)
{
  struct TArgumento *p = (struct TArgumento *) arg;

  for(int i=0; i< 1000; i++)
  {
    printf("%i", p->valor);
    p->valor++;
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t hilo_id[N];
  struct TArgumento parametro;

  for(int i=0; i<N; i++)
  {
  parametro.valor = i;

  pthread_create(&hilo_id, NULL, pinta, &parametro);
  printf("Hola\n");

  pthread_join(hilo_id, NULL);
  return EXIT_SUCCESS;
}
