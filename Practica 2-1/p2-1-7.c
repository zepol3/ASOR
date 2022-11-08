
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(){

    const char *path = "/home/usuario_vms/Descargas";

    printf("número máximo de enlaces: %ld\n", pathconf(path, _PC_LINK_MAX));
	printf("tamaño máximo de una ruta: %ld\n", pathconf(path, _PC_PATH_MAX));
	printf("tamaño máximo de un nombre de fichero: %ld\n", pathconf(path, _PC_NAME_MAX));
	
	return 0;
}