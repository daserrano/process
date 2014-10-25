#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Tnumero {

    int numero;
};

void *operar(void *arg){

    struct Tnumero *n;
    n = (struct Tnumero *)arg;

}

int main(int argc, char *argv[]){

    pthread_t thread1, thread2;
    struct Tnumero num;

    if(thread1)
	num.numero = rand() % 4;
    else
	num.numero = rand() % 3;

    pthread_create(&thread1, NULL, operar,(void *)&num); 
    pthread_create(&thread2, NULL, operar,(void *)&num); 

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
}
