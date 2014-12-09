#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t child = fork();

  if(child)
  {
    // Padre.
    printf("Soy el padre.\n");
  }
  else
  {
    // Hijo.
    printf("Soy el hijo.\n");
    execlp("firefox", "firefox", NULL);
  }
  wait();
  return EXIT_SUCCESS;
}
