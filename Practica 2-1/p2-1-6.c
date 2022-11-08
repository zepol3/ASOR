
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){

    printf("longitud máxima de los argumentos: %ld\n", sysconf(_SC_ARG_MAX));
    printf("número máximo de hijos : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("número máximo de ficheros abiertos: %ld\n", sysconf(_SC_OPEN_MAX));
    
    return 0;
}