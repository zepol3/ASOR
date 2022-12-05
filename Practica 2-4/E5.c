
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER 256

int main(){

    int fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK );
    if(fd1 == -1){
        perror("error al abrir al primera tuberia\n");
        return -1;
    }

    int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK );
    if(fd2 == -1){
        perror("error al abrir al segunda tuberia\n");
        return -1;
    }

    fd_set conjunto;
    FD_ZERO(&conjunto);
    FD_SET(fd1, &conjunto);
    FD_SET(fd2, &conjunto);

    int max;
    if(fd1 > fd2) max = fd1 + 1;
    else max = fd2 + 1;
   
    int seleccion = select(max, &conjunto, NULL, NULL, NULL);
    if(seleccion == -1){
        perror("error en select\n");
        return -1;
    }

    if(seleccion > 0){

        char buff[BUFFER + 1] = {0};
        ssize_t tam  = BUFFER + 1;

        if(FD_ISSET(fd1, &conjunto)){
            while(tam == (BUFFER + 1)){
                tam = read(fd1, buff, BUFFER);
                printf("Fifo1: %s", buff);
            }

            if(tam != 256){
                close(fd1);

                fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK );
                if(fd1 == -1){
                    perror("error al abrir al primera tuberia\n");
                    close(fd1);
                    close(fd2);
                    return -1;
                }
            }
        }
        else if(FD_ISSET(fd2, &conjunto)){
            while(tam == (BUFFER + 1)){
                tam = read(fd2, buff, BUFFER);
                printf("Fifo2: %s", buff);
            }

            if(tam != 256){
                close(fd2);

                fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK );
                if(fd2 == -1){
                    perror("error al abrir al segunda tuberia\n");
                    close(fd1);
                    close(fd2);
                    return -1;
                }
            }
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}





/*terminal 1
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-4$ ./e5
Fifo1: prueba
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-4$ ./e5
Fifo2: prueba
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-4$
*/


/*terminal 2
(base) alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-4$ echo "prueba" > tuberia1
(base) alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-4$ echo "prueba" > tuberia2
*/