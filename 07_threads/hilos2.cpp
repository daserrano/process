#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define NMAX 10000000

sig_atomic_t numero = 0; //Variable para que solo pueda modificar la variable un proceso.

struct Tnumero {

	//int numero;
	int aleatorio;
	int id;
};

void abandonar(int param) {
	if(numero < NMAX)
		printf("\nNo ha terminado el programa va por el numero %i \n", numero);
	else{
		printf("\nHa terminado el programa. %i \n", numero);
		raise(SIGTERM);
	}
}

void *operar(void *arg){

	struct Tnumero *n = (struct Tnumero *)arg;

	while(/*n -> numero*/ numero < NMAX){
		if(n->id == 1){
			n -> aleatorio = rand() % 4;
			/*n ->*/ numero += n -> aleatorio;
			//printf("%i ", /*n ->*/ numero);
		}

		if(n->id == 2){
			n -> aleatorio = rand() % 3; 
			/*n ->*/ numero += n -> aleatorio;
			//printf("%i ", /*n ->*/ numero);
		}
	}
}

int main(int argc, char *argv[]){

	pthread_t thread1, thread2;
	struct Tnumero num;
	//num.numero    = 1;
	num.aleatorio = 0;

	srand(time(NULL));

	if(thread1)
		num.id = 1;
	else
		num.id = 2;

	signal(SIGINT, abandonar);

	pthread_create(&thread1, NULL, operar,(void *)&num); 
	pthread_create(&thread2, NULL, operar,(void *)&num); 

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Pulsa CTRL+C \n");
        while(1);

}
