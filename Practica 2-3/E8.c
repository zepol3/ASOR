
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){

    if(argc < 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("Error en el fork");
        return -1;
    }
    else if (pid == 0){//hijo
        pid_t demon = setsid();
        printf("Hijo: pid = %d, ppid = %d\n", getpid(),getppid());
        close(0);   //cerramos stdin
		close(1);   //cerramos stdout
		close(2);   //cerramos stderr
        
        
        //stdin
        int filein = open("/dev/null", O_CREAT| O_RDWR, 00777);
        if(filein == -1){
            perror("Error al abrir el achivo\n");
            return -1;
        }
        dup2(filein,0);

        //stdout
        int fileout = open("/tmp/daemon.out", O_CREAT| O_RDWR, 00777);
        if(fileout == -1){
            perror("Error al abrir el achivo\n");
            return -1;
        }
        dup2(fileout,1);

        //stderr
        int filerr = open("/tmp/daemon.err", O_CREAT| O_RDWR, 00777);
        if(filerr == -1){
            perror("Error al abrir el achivo\n");
            return -1;
        }
        dup2(filerr,2);
       
        if(execvp(argv[1], argv +1) == -1){
            perror("Error en execvp al ejecutar el comando");
            return -1;
        }
        
    }
    else{//padre
        printf("Padre: pid = %d\n", getpid());
        waitpid(pid, NULL, 0);
    }
    return 0;
}