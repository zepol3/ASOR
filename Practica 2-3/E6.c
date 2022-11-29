
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
        //sleep(30);
        printf("Hijo: pid = %d, ppid = %d\n", getpid(),getppid());
        mostrar();
    }
    else{//padre
        //sleep(30);
        printf("Padre: pid = %d", getpid());
        mostrar();
        waitpid(pid, NULL, 0);
    }
    return 0;
}


/*
proceso hijo tarda mas.
    alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ps -eF
        UID        PID  PPID  C    SZ   RSS PSR STIME TTY          TIME CMD
        root         1     0  1   393   468   0 20:44 ?        00:00:12 /init
        root         9     1  0   224    88   3 20:44 ?        00:00:00 /init
        root        10     9  0   224    88   3 20:44 ?        00:00:00 /init
        alvaro      11    10  0  2543  5236   2 20:44 pts/0    00:00:00 -bash
        root      2813     1  0   393   560   2 21:00 ?        00:00:00 /init
        root      2814  2813  0   393   560   2 21:00 ?        00:00:00 /init
        alvaro    2815  2814  0  2543  5148   3 21:00 pts/1    00:00:00 -bash
        alvaro    2861    11  0   623   568   1 21:02 pts/0    00:00:00 ./E6
        alvaro    2862  2861  0   590    72   2 21:02 ?        00:00:00 ./E6
        alvaro    2863  2815  0  2650  3204   0 21:02 pts/1    00:00:00 ps -eF


proceso padre tarda mas:
    alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ps -eF
        UID        PID  PPID  C    SZ   RSS PSR STIME TTY          TIME CMD
        root         1     0  1   393   720   0 20:44 ?        00:00:13 /init
        root         9     1  0   224    88   3 20:44 ?        00:00:00 /init
        root        10     9  0   224    88   0 20:44 ?        00:00:00 /init
        alvaro      11    10  0  2543  5236   2 20:44 pts/0    00:00:00 -bash
        root      2813     1  0   393   560   2 21:00 ?        00:00:00 /init
        root      2814  2813  0   393   560   3 21:00 ?        00:00:00 /init
        alvaro    2815  2814  0  2543  5148   3 21:00 pts/1    00:00:00 -bash
        alvaro    3157    11  0   590   572   0 21:05 pts/0    00:00:00 ./E6
        alvaro    3158  3157  0     0     0   2 21:05 ?        00:00:00 [E6] <defunct>      <--------
        alvaro    3159  2815  0  2650  3216   1 21:05 pts/1    00:00:00 ps -eF

*/