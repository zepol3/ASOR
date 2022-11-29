
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

int mostrar(){//copiada de E5.c
    pid_t pid, ppid, pgid, sid;
    int max;

    pid = getpid();
    ppid = getppid();
    pgid = getpgid(pid);
    sid = getsid(pid);

    struct  rlimit limite;
    if(getrlimit(RLIMIT_NOFILE, &limite) == -1){
        perror("Error al buscar el limite");
        exit(EXIT_FAILURE);
    }

    max = limite.rlim_cur;

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid); 
    printf("GPID: %d\n", pgid);
    printf("SID: %d\n", sid);
    printf("Nº max ficheros: %d\n", max);
    printf("Directorio actual: %s\n", getcwd(NULL, pid));
}



int main(){

    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("Error en el fork");
        return -1;
    }
    else if (pid == 0){//hijo
        pid_t demon = setsid();
        if(chdir("/tmp") == -1){
            perror("Error al cambiar el directorio");
            return -1;
        }
        printf("Hijo: pid = %d, ppid = %d\n", getpid(),getppid());
        mostrar();
    }
    else{//padre
        printf("Padre: pid = %d", getpid());
        mostrar();
        waitpid(pid, NULL, 0);
    }
    return 0;
}