
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
    
    if(argc < 4){
        perror("Numero invalido de argumentos\n");
        return -1;
    }


    struct addrinfo hints;
    struct addrinfo *resultado;
    
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
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

    if(sendto(sockett, argv[3], sizeof(argv[3]), 0, resultado->ai_addr, resultado->ai_addrlen) == -1){
        perror("Error al enviar el comando\n");
        return -1;
    }

    if(*argv[3] == 't' || *argv[3] == 'd'){
        
        struct sockaddr_storage client_addr;
	    socklen_t client_addrlen = sizeof(client_addr);
        
        char buff[BUFFER + 1];
        size_t l = recvfrom(sockett, buff, BUFFER, 0, (struct sockaddr *) &client_addr, &client_addrlen);
    
        if(l == -1){
            perror("erro al recibir la respuesta\n");
            return -1;
        }    
        buff[l] = '\0';

        printf("Respuesta: %s", buff);
    }

    return 0;
}



/*
dos terminales 
netcat
ss -uan*/