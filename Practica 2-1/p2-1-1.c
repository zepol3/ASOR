
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
   
    char *error;
    if (setuid(0) == -1){
        perror(error);
    }
   
exit(EXIT_SUCCESS);
}