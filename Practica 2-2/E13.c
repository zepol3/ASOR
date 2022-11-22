
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

    if (dup2(file, 1) == -1 | dup2(file,2)== -1) {
        perror("Error");
    }
    else{
        printf("todo funciona bien\n");
        perror("Seguimos tranquilos aqui");
        
    }
    close(file);
    return 0;
}





/*
da igual el orden en el que se pongan las instrucciones, siempre va primero el error y luego el resto
ls > dirlist 2>&1 y ls 2>&1 > dirlist
me salen con el mismo ressultado, supongo que esta mal, si no no tiene sentido la pregunta
*/