
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

#define BUFFER 128

int main(int argc, char *argv[]){
    
    if(argc < 3){
        perror("Numero invalido de argumentos\n");
        return -1;
    }


    struct addrinfo hints;
    struct addrinfo *resultado;
    
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(argv[1], argv[2], &hints, &resultado);

    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }

    int sockett = socket(resultado->ai_family, resultado->ai_socktype, resultado->ai_protocol);

    if(sockett == -1){
        perror("Error al crear socket\n");
        return -1;
    }

    if(connect(sockett, resultado->ai_addr, resultado->ai_addrlen) == -1){
        perror("Error al conectar el socket\n");
        return -1;
    }

    while(1){
        
        char buff[BUFFER + 1];
        fgets(buff, BUFFER, stdin);
        buff[strlen(buff) - 1] = '\0';

        size_t envio = send(sockett, buff, sizeof(buff), 0);
        if(envio == -1){
            perror("error al enviar el mensaje\n");
            return -1;
        }
        if(strcmp(buff, "Q") != 0){
            char mensaje[BUFFER + 1];

            size_t mens = recv(sockett, mensaje, BUFFER, 0);
            if(mens == -1){
                perror("Error al recibir la respuesta\n");
                return -1;
            }
            mensaje[mens] = '\0';
            printf("respuesta: %s\n", mensaje);
        }
        else{
            close(sockett);
            return 0;
        }
    }

    return 0;
}



/*
dos terminales 
netcat
ss -uan*/