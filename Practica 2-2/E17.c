
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc,char **argv){

    if(argc != 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    DIR *directorio = opendir(argv[1]);
    if(directorio == NULL){
        perror("Error al abrir el directorio\n");
        return -1;
    }

    struct stat informacion;
    struct dirent * actual;
    off_t total = 0;
    while ((actual = readdir(directorio)) != NULL){

        char *path = malloc(sizeof(char) *(strlen(argv[1]) + strlen(actual -> d_name) + 3));

        sprintf(path, "%s/%s", argv[1], actual -> d_name);

        if(stat(path, &informacion) == -1){
            perror("no se ha podido acceder a una de las entradas del directorio");
            closedir(directorio);
            return -1;
        }

        if(S_ISLNK(informacion.st_mode)){
            char *linkname = (char * ) malloc( informacion.st_size + 1);
            readlink(path, linkname, informacion.st_size + 1);

            printf("%s -> %s\n", actual -> d_name, linkname);
        }
        else if(S_ISDIR(informacion.st_mode)){

            printf("/%s\n", actual -> d_name);

        }
        else if (S_ISREG(informacion.st_mode))
        {
            printf("Fichero regular: %s", actual -> d_name);
            if((informacion.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) > 0){
                    printf(" *");
            }
            printf("\n");
            total += informacion.st_size;
        }
        free(path);
    }

    closedir(directorio);
    float kb = total/ 1000;
    printf("total kb: %f", kb);
    return 0;
}