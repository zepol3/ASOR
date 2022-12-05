
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    int file[2];
    pid_t pid;

    if(pipe(file) == -1){
        perror("error al crear la tuberia\n");
        return -1;
    }

    pid = fork();

    if(pid < 0){
        perror("Error en el fork");
        return -1;
    }
    else if (pid == 0){//hijo

        printf("Hijo: pid = %d, ppid = %d\n", getpid(),getppid());
        close(file[1]);
        dup2(file[0], 0);
		close(file[0]);
        execlp(argv[3], argv[3], argv[4], NULL);
    }
    else{//padre
        printf("Padre: pid = %d\n", getpid());
        close(file[0]);
        dup2(file[1], 1);
		close(file[1]);
        execlp(argv[1], argv[1], argv[2], NULL);
    }
    return 0;
}