#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

#include "common.h"

#define BACKLOG 5
#define N 32

struct TArg
{
    int fd;
    char origin[N];
};

int usuarios = 0;

void *rec(void *args)
{
    struct TArg *arg = (struct TArg *) args;
    int fd = arg->fd;
    int r = 0;
    int respuesta = false;
    char buffer[50];

    pthread_detach(pthread_self());

    do{
	do{
	    r = recibir(fd, buffer);
	    if(r){
		if(!strcmp(buffer, "quit"))
		    respuesta = true;
		printf("%s : %s\n", arg->origin, buffer);
	    }
	}while(r);
    }while(!respuesta);

    close(fd);
    usuarios--;
    printf("%i\n", usuarios);
    return NULL;
}

    int main(int argc, char *argv[]){
	int socket_fd; // Fichero para escuchar llamadas.
	struct sockaddr_in address; // Configuracion servidor.

	if(argc < 2)
	{
	    fprintf(stderr, "%s <numero de puerto>\n", argv[0]);
	    return EXIT_FAILURE;
	}

	if ( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) //Crear socket.
	    error("Socket");

	address.sin_family = AF_INET; // Tipo de socket.
	address.sin_port = htons( atoi(argv[1]) ); // Puerto de escucha.
	address.sin_addr.s_addr = INADDR_ANY; // Tipo de conexion.
	bzero(&address.sin_zero, sizeof(address.sin_zero)); // Rellenar con 0 los 8 bits.

	if ( bind(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr) ) == -1) // Enlazar socket.
	    error("Bind");

	if ( listen(socket_fd, BACKLOG) == -1) // Listo para escuchar comunicaciones.
	    error("Listen");

	while(1)
	{
	    int client_fd;
	    pthread_t thread_id;
	    char buffer[50]; // Buffer para comunicacion.
	    socklen_t len = (socklen_t) sizeof(struct sockaddr); //Tamaño mensaje.
	    struct TArg args;
	    struct sockaddr_in client_config; 

	    const char *mensajeBienvenida;

	    mensajeBienvenida = "Bienvenido al nuevo servidor de Apache.";

	    printf("\n%s\n\n", mensajeBienvenida);

	    if((client_fd = accept(socket_fd, (struct sockaddr *) &client_config, &len)) == -1) // Aceptar conexion cliente.
		error("Accept");

	    args.fd = client_fd;
	    strncpy(args.origin, inet_ntoa(client_config.sin_addr), N);
	    args.origin[N-1] = '\0';

	    pthread_create(&thread_id, NULL, &rec, &args);
	    usuarios++;

	    close(client_fd); // Cerrar conexion.
	}

	close(socket_fd);

	return EXIT_SUCCESS;
    }
