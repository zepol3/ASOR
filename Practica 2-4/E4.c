
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    int tuberia = open("tuberia", O_CREAT | O_WRONLY, 0666);

    write(tuberia, argv[1], strlen(argv[1]));

    close(tuberia);

    return 0;
}