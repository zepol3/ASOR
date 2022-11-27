
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

    while ((actual = readdir(directorio)) != NULL){

        char *path = (char *) malloc(sizeof(char) * (strlen(argv[1]) + (actual -> d_name) + 3));

        sprintf(path, "%s/%s", argv[1], actual -> d_name);

        if(stat(path, &informacion) == -1){
            perror("no se ha podido acceder a una de las entradas del directorio");
            close(directorio);
            return -1;
        }

        if(S_ISLNK(informacion.st_mode)){

        }
        else if(S_ISDIR(informacion.st_mode)){

        }
        else if (S_ISREG(informacion.st_mode))
        {
            /* code */
        }
        
    }
    
}