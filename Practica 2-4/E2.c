
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER 1024

int main(){

    int p_h[2];
    int h_p[2];

    pid_t pid;

    if(pipe(p_h) == -1){
        perror("error al crear la tuberia p_h\n");
        return -1;
    }
    if(pipe(h_p) == -1){
        perror("error al crear la tuberia h_p\n");
        return -1;
    }

    pid = fork();

    if(pid < 0){
        perror("Error en el fork");
        return -1;
    }
    else if (pid == 0){//hijo
        printf("Hijo: pid = %d, ppid = %d\n", getpid(),getppid());
        close(p_h[1]);
        close(h_p[0]);
        char buff[BUFFER + 1];
        ssize_t tamano = 0;
        int recibidos;
        while(recibidos < 10){
            tamano = read(p_h[0], &buff, BUFFER);
            if ( tamano == -1){
                perror("error al leer del padre\n");
                return -1;
            }
            recibidos ++;

            printf("Mensaje: %s\n", buff);

            sleep(1);

            if(write(h_p[1], "l", 1) == -1){
                perror("Error al escribir al padre l\n");
                return -1;
            }       
        }

        if(write(h_p[1], "q", 1) == -1){
            perror("Error al escribir al padre q\n");
            return -1;
        }
        
		close(p_h[0]);
        close(h_p[1]);
    }
    else{//padre
        printf("Padre: pid = %d\n", getpid());
        close(p_h[0]);
        close(h_p[1]);
        char buff[BUFFER + 1];
        char child[1] = {'l'};
        ssize_t tamano = 0;
        int recibidos;
        while(child[0] != 'q'){
            tamano = read(0, &buff, BUFFER);
            if ( tamano == -1){
                perror("error al leer de la terminal\n");
                return -1;
            }

            buff[tamano - 1] = '\0';

            if(write(p_h[1], buff, tamano) == -1){
                perror("Error al escribir al hijo l\n");
                return -1;
            }
            
            tamano = read( h_p[0], child, 1);
            if ( tamano == -1){
                perror("error al leer del hijo\n");
                return -1;
            }
        }
        
		close(p_h[1]);
        close(h_p[0]);
        printf("fin\n");
    }
    return 0;
}