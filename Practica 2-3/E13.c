
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

volatile int stop = 0;
volatile int mata = 0;

void handler(int senal){
    if(senal == SIGUSR1) stop = 1;
    if(senal == SIGALRM) mata = 1;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }   

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_UNBLOCK, &set,NULL);
    
    struct sigaction sig;
    int time = atoi(argv[1]);
    alarm(time);

    sig.sa_handler = handler;
    if(sigaction(SIGUSR1, &sig, NULL) == -1){
        perror("error al cambiarl el controlador para SIGUSR1");
        return -1;
    }
    if(sigaction(SIGALRM, &sig, NULL) == -1){
        perror("error al cambiarl el controlador para SIGALRM");
        return -1;
    }

    int x = 0;
    sigset_t espera;
    while(!stop && !mata){
        sigsuspend(&espera);
    }
    
    if(stop){
        printf("no se borra nada\n");
    }
    else{
        printf("borramos el ejecutable\n");
        if(unlink(argv[0]) == -1){
            perror("fallo al borrar el ejecutable\n");
        }
    }
    return 0;
}



/*ps -C e13
para ver el pid del proceso y poder usar kill
 kill -s SIGUSR1 28689
*/