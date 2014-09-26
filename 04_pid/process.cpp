#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Process ID: %d\nProcess Parent ID: %d\n", getpid(),getppid());

    return 0;
}
