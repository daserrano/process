#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* hola (void* unused) {

int contador2;
	while(100){
		printf(" Hola don Jose ");
		contador2++;
}
return contador2;
}

int main(int argc, char *argv[]) {

	pthread_t thread_id; 
int contador=0;

	pthread_create (&thread_id, NULL, &hola, NULL);
	while(100) {
		printf("Hola don Pepito ");
	contador++;
}

	pthread_join(thread_id, NULL);
printf("%i ", contador);

	return EXIT_SUCCESS;
}
