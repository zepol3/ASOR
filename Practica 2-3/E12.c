
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

volatile int contador_SIGINT = 0;
volatile int contador_SIGSTOP = 0;

void handler(int senal){
    if(senal == SIGINT) contador_SIGINT++;
    if(senal == SIGTSTP) contador_SIGSTOP++;
}

int main(){

    struct sigaction sig;

    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART;
    
    sig.sa_handler = handler;
    if(sigaction(SIGINT, &sig, NULL) == -1){
        perror("error al cambiarl el controlador para SIGINT");
        return -1;
    }
    if(sigaction(SIGTSTP, &sig, NULL) == -1){
        perror("error al cambiarl el controlador para SIGSTOP");
        return -1;
    }

    

    sigset_t set;
    sigemptyset(&set);

    while((contador_SIGINT + contador_SIGSTOP) < 10){
        sigsuspend(&set);
    }

    printf("hemos capturado %d SIGINT\n", contador_SIGINT);
    printf("hemos capturado %d SIGSTOP\n", contador_SIGSTOP);

    return 0;
}