#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

void error(const char *mssg)
{
    perror(mssg);
    exit(EXIT_FAILURE);
}

int recibir(int fd, char *buffer)
{
    int length;
    read(fd, &length, sizeof(length));
    return read(fd, buffer, length);
}

int enviar(int fd, const char *mssg)
{
    int length;
    length = strlen(mssg) + 1;
    write(fd, &length, sizeof(length));
    write(fd, mssg, length);
}
