#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "common.h" //Libreria que se crea para compartir funciones.

int main(int argc, char *argv[])
{
  
  int socket_fd;
  struct sockaddr_in address;
  struct hostent *he;

  if ( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    ohoh("socket");

  address.sin_family = AF_INET;
  he = gethostbyname(argv[1]);
  address.sin_address = *( (struct in_addr *) he->haddr);
  address.sin_port = htons(atoi(argv[2]));
  bzero(&address.sin_zero, sizeof(address.sin_zero));

  connect(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr));

  char buffer[] = "Hola";
  int len = sizeof(buffer);
  write(socket_fd, &len, sizeof(len));
  write(socket_fd, buffer, len);

  close(socket_fd);

  return EXIT_SUCCESS;
}
