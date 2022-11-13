

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main()
{
	printf("User UID: %d\n", getuid());
	printf("User EUID: %d\n", geteuid());
/*Modificar el programa anterior para que muestre además el nombre de usuario, el directorio home y la descripción del usuario.
*/
    struct passwd *user = getpwuid(getuid());
	printf("Nombre user: %s\n", user->pw_name);
	printf("Directorio user: %s\n", user->pw_dir);
	printf("descripción user: %s\n", user->pw_gecos);
	
	return 0;
}