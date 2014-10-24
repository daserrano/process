#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 3

struct TMatriz {
	int id;
	int escalar;
	int matriz[N][N];
};

void inicializar(int mat[N][N]){

	for(int i=0; i<2; i++)
		for(int j=0; j<2; j++)
			mat[i][j] = random() * 100;
}

void *multiplicar(void *arg){

	struct TMatriz *ma;
	int i=0, j=0;
	ma = (struct TMatriz *)arg;

	for(i; i<2; i++)
		printf("El hilo %i multiplicando fila %i \n", ma -> id, i);
	for(j; j<2; j++)
		ma -> matriz[i][j] += ma -> escalar;
}

void pintarMatriz(int matriz[N][N]){

	int i=0, j=0;

	for (i; i<2; i++)
		printf("\n");
	for (j; j<2; j++)
		printf("%i ", matriz[i][j] = matriz[i][j]);
}

int main(int argc, char *argv[]){
	pthread_t hilo1, hilo2;
	struct TMatriz m1, m2;

	m1.id = 1;
	m1.escalar = 2;
	m2.id = 2;
	m2.escalar = 3;

	inicializar(m1.matriz);
	inicializar(m2.matriz);

	pthread_create(&hilo1, NULL, multiplicar , (void *)&m1);
	pthread_create(&hilo2, NULL, multiplicar , (void *)&m2);

	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	printf("Ok.");

	pintarMatriz(m1.matriz);
	pintarMatriz(m2.matriz);

	printf("\n");

	return EXIT_SUCCESS;
}
