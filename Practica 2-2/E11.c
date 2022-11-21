
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(int argc,char **argv){

    if(argc != 2){
        perror("Tienes que pasar la ruta del fichero");
        return -1;
    }

    struct stat _stat;
    stat(argv[1], &_stat);

    if(S_ISREG(_stat.st_mode)){     //si es un ficher regular modifico el tipo de enlace
        string hardLink = string(argv[1])+ ".hard";
        string symbolicLink = string(argv[1])+ ".sym";
        

    }