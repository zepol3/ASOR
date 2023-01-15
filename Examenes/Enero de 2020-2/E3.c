/*NO FUNCIONA*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        perror("numero invalido de argumentos");
        return -1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    pid = fork();

    if (pid == -1)
    {
        perror("error en fork\n");
        return -1;
    }
    else if (pid == 0)
    { // hijo

        printf("PID:%d\n", getpid());
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        if (execvp(argv[2], argv + 2) == -1)
        {
            perror("error al ejecutar la instruccion en hijo 2\n");
            return -1;
        }
        close(pipefd[0]);
    }
    else
    { // padre
        printf("PID:%d\n", getpid());
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        if (execlp(argv[1], "", NULL) == -1)
        {
            perror("error al ejecutar la instruccion en hijo 1\n");
            return -1;
        }
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}