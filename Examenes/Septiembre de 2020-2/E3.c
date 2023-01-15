#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("numero invalido de argumentos\n");
        return -1;
    }

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("error al crear el hijo\n");
        return -1;
    }
    else if (pid == 0)
    { // hijo
        pid_t news = setsid();
        if (news == -1)
        {
            perror("error al cambiar la sesion\n");
            exit(EXIT_FAILURE);
        }

        if (chdir("/tmp") == -1)
        {
            perror("error al cambiar el directorio de trabajo\n");
            exit(EXIT_FAILURE);
        }
        printf("identificadores de proceso: %d\n", getpid());
        printf("identificadores de proceso padre: %d\n", getppid());
        printf("identificadores de grupo: %d\n", getpgid(getpid()));
        printf("identificadores de sesion: %d\n", getsid(getpid()));

        if (execvp(argv[1], argv + 1) == -1)
        {
            perror("error al ejecutar el programa\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    { // padre
        exit(EXIT_SUCCESS);
    }
    return 0;
}