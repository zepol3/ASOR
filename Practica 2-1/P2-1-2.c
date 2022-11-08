
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){

	if (setuid(0) == -1){

		printf("Error %d: %s\n", errno, strerror(errno));

	}

	exit(EXIT_SUCCESS);
}