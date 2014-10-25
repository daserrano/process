#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hola (void* unused) {

    while(100)
	printf(" Hola don Jose ");
}

int main(int argc, char *argv[]) {

    pthread_t thread_id; 

    pthread_create (&thread_id, NULL, &hola, NULL);
    while(100) {
	printf("Hola don Pepito ");
    }

    pthread_join(thread_id, NULL);

    return EXIT_SUCCESS;
}
