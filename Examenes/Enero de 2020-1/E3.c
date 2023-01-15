
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/select.h>  

#define BUFFER 500

int main(){
    int tuberia1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
    if(tuberia1 == -1){
        perror("Error al abrir tuberia 1\n");
        return -1;
    }
    int tuberia2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
    if(tuberia2 == -1){
        perror("Error al abrir tuberia 2\n");
        return -1;
    }
    
    int max;
    int seleccion;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(tuberia1, &rfds);
    FD_SET(tuberia2, &rfds);

    while(1){
        FD_ZERO(&rfds);
        FD_SET(tuberia1, &rfds);
        FD_SET(tuberia2, &rfds);

        if(tuberia1 > tuberia2) max = tuberia1 + 1;
        else    max = tuberia2 + 1;

        seleccion = select(max, &rfds, NULL, NULL, NULL);
        if(seleccion == -1){
            perror("Error al selsccionar tuberia\n");
            return -1;
        }
        else if(seleccion > 0){
            char buff[BUFFER] = {0};
            ssize_t tamno = BUFFER;

            if(FD_ISSET(tuberia1, &rfds)){//cambiar esto
                int comprobar = read(tuberia1, buff, BUFFER);
                printf("[PIPE 1]: %s", buff);
                
                close(tuberia1);
                tuberia1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
                if(tuberia1 == -1){
                    perror("Error al abrir tuberia 1\n");
                    return -1;
                }               
            }

            if(FD_ISSET(tuberia2, &rfds)){//cambiar esto
                int comprobar = read(tuberia2, buff, BUFFER);
                printf("[PIPE 2]: %s", buff);
                
                close(tuberia2);
                tuberia2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
                if(tuberia2 == -1){
                    perror("Error al abrir tuberia 2\n");
                    return -1;
                }
            }
        }
    }
    close(tuberia1);
    close(tuberia2);
    return 0;
}