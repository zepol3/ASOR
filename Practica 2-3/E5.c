
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
    pid_t pid, ppid, pgid, sid;
    int max;

    pid = getpid();
    ppid = getppid();
    pgid = getpgid(pid);
    sid = getsid(pid);

    struct  rlimit limite;
    if(getrlimit(RLIMIT_NOFILE, &limite) == -1){
        perror("Error al buscar el limite");
        return -1;
    }

    max = limite.rlim_cur;

    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid); 
    printf("GPID: %d\n", pgid);
    printf("SID: %d\n", sid);
    printf("Nº max ficheros: %d\n", max);
    printf("Directorio actual: %s\n", getcwd(NULL, pid));
    
    
    return 0;
}




/*
OUTPUT:
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ./E5
PID: 10509
PPID: 3225
GPID: 10509
SID: 3225
Nº max ficheros: 1024
Directorio actual: /home/alvaro/ASOR/Practica 2-3
*/