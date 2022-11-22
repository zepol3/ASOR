
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char **argv){
    
    if(argc != 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    int file = open(argv[1], O_CREAT| O_RDWR, S_IRUSR|S_IWUSR);
    if(file == -1){
        perror("Error al abrir el achivo\n");
        return -1;
    }

    if (dup2(file, 1) == -1) {
        perror("Error");
    }
    else{
        printf("todo funciona bien\n");
    }
    close(file);
    return 0;
}