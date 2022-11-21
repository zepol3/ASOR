
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv){

    if(argc != 2){
        perror("Tienes que pasar la ruta del fichero\n");
        return -1;
    }
    char* path = argv[1];
    struct stat _stat;
    stat(path, &_stat);

    if(S_ISREG(_stat.st_mode)){     //si es un ficher regular modifico el tipo de enlace
        char* hardLink = malloc(sizeof(char)*(strlen(path)+ strlen(".hard")));
        char* symbolicLink = malloc(sizeof(char)*(strlen(path)+ strlen(".sym")));
        
        hardLink = strcat(strcpy(hardLink, path), ".hard");
        symbolicLink = strcat(strcpy(symbolicLink, path), ".sym");

        if(link(path,hardLink) == 0){
            printf("Exito al crear el enlace rigido\n");
        }
        else{
            perror("No se ha conseguido crear el enlace rigido\n");
        }

        if(symlink(path, symbolicLink) == 0){
            printf("Exito al crear el enlace simbolico\n");
        }
        else{
            perror("No se ha conseguido crear el enlace simbolico\n");
        }
    }
    else{
        perror("El path no es un fichero");
    }
}