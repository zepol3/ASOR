
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(){
    
    sigset_t senal;

    if(sigemptyset(&senal) == -1){//inicializa un conjunto como vacío, excluyendo todas las señales
        perror("error al iniciar el conjunto\n");
        return -1;
    }

    if(sigaddset(&senal, SIGINT) == -1){//añade una señal a un conjunto
        perror("error al añadir la señal SIGINT al conjunto\n");
        return -1;
    }

    if(sigaddset(&senal, SIGSTOP) == -1){//añade una señal a un conjunto
        perror("error al añadir la señal SIGTSTP al conjunto\n");
        return -1;
    }
    
    if(sigprocmask(SIG_BLOCK, &senal, NULL) == -1){
        perror("error al BLOQUEAR las señales\n");
        return -1;
    }

    char *sleep_secs = getenv("SLEEP_SECS");
    if(sleep_secs == NULL){
        perror("no se esncontro sleep_secs");
        return -1;
    }
    sleep(atoi(sleep_secs));
    
    sigset_t pending;
    sigemptyset(&pending);
    if(sigpending(&senal) == -1){//Comprobar señales pendientes
        perror("error al comprobar las pendientes\n");
        return -1;
    }

    if(sigismember(&pending, SIGINT) == -1){//comprueba si una señal pertenece a un conjunto
        printf("recibido SIGINT\n");
    }
    
    if(sigismember(&pending, SIGSTOP) == -1){//comprueba si una señal pertenece a un conjunto
        printf("recibido SIGTSTP\n");
        //al recibir la señal SIGTSTP, procedemos a desbloquearla
        if(sigdelset(&senal, SIGSTOP) == -1){// elimina una señal de un conjunto
            perror("error al liberar la señal\n");
            return -1;
        }

        if(sigprocmask(SIG_UNBLOCK, &senal, NULL) == -1){
            perror("error al DESBLOQUEAR las señales\n");
            return -1;
        }
    }
    printf("se ha desbloquedado SIGSTOP\n");
    return 0;
}