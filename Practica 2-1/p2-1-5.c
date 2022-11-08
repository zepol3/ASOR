
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

int main(){

    struct utsname sistemInfo;

    if(uname(&sistemInfo) == -1){
        printf("Error %d: %s\n", errno, strerror(errno));
    }
    else{
        printf("Nombre del sistema: %s\n", sistemInfo.sysname);
        printf("Nombre de la maquina: %s\n", sistemInfo.nodename);
		printf("Lanzamiento: %s\n", sistemInfo.release);
		printf("Version: %s\n", sistemInfo.version);
		printf("Identificador de la maquina: %s\n", sistemInfo.machine);
	}


    return 0;
}