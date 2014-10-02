#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int spawn(const char* program, char** arg_list)
{
    pid_t child_pid=0;

    child_pid = fork();
    if(child_pid == 0){
	execvp(program, arg_list);
	fprintf(stderr, "Error with execvp\n");
	abort();
    }
    else
	return child_pid;
}

int main(int argc, char *argv[])
{
    int opcion;
    char *arg_list[] = {
	"www.google.es",
	NULL
    };

    printf("Bienvenido Compañero.\n\n");
    while(opcion!=3)
    {
	printf("MENU\n");
	printf("1. Ls\n");
	printf("2. Google\n");
	printf("3. Salir\n");
	scanf("%i", &opcion);

	switch(opcion)
	{
	    case 1:
		printf("ls");
		break;
	    case 2:
		spawn("firefox", arg_list);
		break;
	    case 3:
		return EXIT_SUCCESS;
		break;
	}
    }
    return EXIT_SUCCESS;
}
