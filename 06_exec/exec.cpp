#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int spawn(char* program, char ** arg_list)
{
	pid_t child_pid;

	child_pid = fork();
	if(child_pid == 0)
		execvp(program, arg_list);

}

int main(int argc, char *argv[])
{
	int opcion;
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
				char* arg_list[] = {
					"ls",
					"/",
					NULL
				};
				spawn("ls", arg_list);
				break;
			case 2:
				break;
			case 3:
				return EXIT_SUCCESS;
				break;
		}
	}
}
