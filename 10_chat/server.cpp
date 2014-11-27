#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // in -> internet.
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#define BACKLOG 5

void ohoh(const char *mssg) // Función para mostrar mensaje de perror.
{
  perror(mssg);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  int incomming_socket;     // Se crea un fichero para que el servidor escuche llamadas.
  struct sockaddr_in address; // Configuracion del servidor.

  /* Crear el socket */
  if(argc < 2){  // Si hay menos de 2 argumentos.
    fprintf(stderr, "%s <numero de puerto\n", argv[0]);
    return EXIT_FAILURE;
  }

  if( (incomming_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) //AF_INET= Socket de internet, SOCK_STREAM=socket de flujo, 0 -> elige el protocolo que mejor conviene.
    ohoh("Socket");

  /* BIND */
  address.sin_family = AF_INET;                          // Se indica de que familia es el socket.
  address.sin_port = htons( atoi(argv[1]) );             // Indica que puerto, y como es una cadena de caracteres hay que transformarlo a entero.
  address.sin_addr.s_addr = /*inet_aton("0.0.0.0", &address.sin_addr)*/ INADDR_ANY;        // inet_aton = convierte la direccion IP en hexadecimal y le da la vuelta a los bits. 0.0.0.0 permite la conexion desde el interior y exterior.
  //memset(address.sin_zero, 0, sizeof(address.sin_zero)); // Rellena con 0 los 8 bits de sin_zero.
  bzero(address.sin_zero, sizeof(address.sin_zero));       // Rellena con 0 los 8 bits de sin_zero.

  if( bind(incomming_socket, (struct sockaddr *) &address, sizeof(address) ) == -1) // sockaddr * -> molde de la estructura sockaddr_in a una estructura generica.
    ohoh("Bind");

  if ( listen(incomming_socket, BACKLOG) == -1)  // Escucha las comunicaciones hasta lo que valga el parametro BACKLOG.
    ohoh("Listen");

  while(1)
  {
    int client_fd;
    char buffer[80];
    socklen_t len; // Se utiliza para el tamaño del mensaje que introduza el cliente.

    struct sockaddr_in client_config;

    client_fd = accept(incomming_socket, (struct sockaddr *) &client_config, &len); // Acepta la conexion del cliente.

    read(client_fd, buffer, 80); // Se crea un buffer para leer lo que introduzca el usuario.
    printf("%s \n", buffer);
    close(client_fd); // Cierra la conexion.

  }

  return EXIT_SUCCESS;

}
