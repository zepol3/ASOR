
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERRORES_MAX 255

int main(){

	for(int x = 0; x < 255; x++){

		printf("Error %d: %s\n", x, strerror(x));

    }
	exit(EXIT_SUCCESS);
}