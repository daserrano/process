#include <stdio.h>
#include <stdlib.h>
#include "library.hpp"

int main(int argc, char **argv){

    double op1, op2;

    op1 = atof(argv[1]);
    op2 = atof(argv[2]);

	printf("%.2lf + %.2lf = %.2lf\n", op1, op2, suma(op1, op2));
    
    return 0;
}
