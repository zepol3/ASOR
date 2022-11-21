
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(){

    struct stat buff;

    int file = open("prueba9.txt", O_CREAT| O_RDWR | O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH|S_IXOTH);
 

    if(file == -1){
        perror("No se ha conseguido abrir el archivo");
        return -1;
    }

    if(fstat(file, &buff) == -1){
        perror("No se han conseguido obtener los atributos");
    }
    else{
        printf("Major: %d\n", major(buff.st_dev));
        printf("Minor: %d\n", minor(buff.st_dev));
        printf("Inode: %ld\n", buff.st_ino);

        char *tipo;

        if(S_ISREG(buff.st_mode)){
            tipo = "Fichero regular";
        }

        if(S_ISDIR(buff.st_mode)){
            tipo = "Directorio";
        }

        if(S_ISLNK(buff.st_mode)){
            tipo = "Enlace simbolico";
        }
        printf("Modo: %s\n", tipo);

        printf("Last file modification:   %s", ctime(&buff.st_mtime));
        printf("Last status change:       %s", ctime(&buff.st_ctime));
    }

    close(file);
    return 0;
}