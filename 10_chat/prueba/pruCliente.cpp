#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "common.h"

void conexion(int *socket_fd, const char *ip, int puerto)
{
    struct sockaddr_in address; //Configuracion socket.
    struct hostent *he; //Nombre host.
    
    if( (*socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) //Crear socket.
	error("Socket");

    address.sin_family = AF_INET; //Familia del socket.
    if( (he = gethostbyname(ip)) == NULL)
	error("Dns");
    address.sin_addr = *((struct in_addr *) he->h_addr);
    address.sin_port = htons(puerto);
    bzero(&address.sin_zero, sizeof(address.sin_zero));

    if( connect(*socket_fd, (struct sockaddr *) &address, sizeof(struct  sockaddr)) == -1)
	error("Conexion");
 }

void mensaje(int *socket_fd)
{
    int respuesta = 0;
    char buffer[50];

    recibir(*socket_fd, buffer);
    printf("%s", buffer);
    do
    {
	char *line = readline("Usuario : ");
	if (line && *line)
	    add_history (line);
	enviar(*socket_fd, line);

	if(!strcasecmp(line, "quit"))
	    respuesta = 1;

	free(line);
    }while(!respuesta);
}
int main(int argc, char *argv[])
{
    int socket_fd; 

    if( argc < 3){
	fprintf(stderr, "%s <IP> <puerto>\n", argv[0]);
	return EXIT_FAILURE;
    } 

    conexion(&socket_fd, argv[1], atoi(argv[2]));
    mensaje(&socket_fd);

    close(socket_fd);

    return EXIT_SUCCESS;
}
