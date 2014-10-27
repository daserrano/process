#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct Tnumero {

    int numero;
    int aleatorio;
    int id;
};

void *operar(void *arg){

    struct Tnumero *n = (struct Tnumero *)arg;

    while(n -> numero < 10000){
	if(n->id = 1){
	    n -> aleatorio = rand() % 4;
	    n -> numero += n -> aleatorio;
	    printf("%i ", n -> numero);
	}

	if(n->id = 2){
	    n -> aleatorio = rand() % 3; 
	    n -> numero += n -> aleatorio;
	    printf("%i ", n -> numero);
	}
    }
}

int main(int argc, char *argv[]){

    pthread_t thread1, thread2;
    struct Tnumero num;
    num.numero    = 1;
    num.aleatorio = 0;

    srand(time(NULL));

    if(thread1)
	num.id = 1;
    else
	num.id = 2;

    pthread_create(&thread1, NULL, operar,(void *)&num); 
    pthread_create(&thread2, NULL, operar,(void *)&num); 

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\n");

}
