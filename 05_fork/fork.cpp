#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    static int contador = 0;
    /*printf("We came\n");
      fork();
      printf("We love\n");
      fork();
      printf("We raved\n");
     */
    for(int i=0; i<3; i++){
	contador++;
	printf("%i. No me gustan los buenos dias!\n", contador);
	fork();
    }
    return EXIT_SUCCESS;
}
