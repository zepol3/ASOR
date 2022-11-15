#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main(){

    umask(S_IWGRP | S_IXOTH);

    int file = open("prueba7.txt", O_CREAT| O_RDWR | O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH|S_IXOTH);
    
    if(file == -1){
        perror("Fallo");
        return -1;
    }
    else{
        close(file);
        printf("el fichero se ha creado correctamente\n");
    }

    return 0;
}