
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
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER 128
#define LISTEN_BACKLOG 5

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

    if (bind(sockett, resultado->ai_addr, resultado->ai_addrlen) != 0) {
        perror("Error al ejecutar el bind\n");
        return -1;
    }

    freeaddrinfo(resultado);

    for (int i = 0; i < 5; i++){///cuantas veces tengo que ejecutar esto??
        if(listen(sockett, LISTEN_BACKLOG) == -1){
            perror("Error en listen\n");
            return -1;
        }

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        struct sockaddr_storage client_addr;
        socklen_t client_addrlen = sizeof(client_addr);
        
        int cliente = accept(sockett,(struct sockaddr *)&client_addr, &client_addrlen);
        if(cliente == -1){
            perror("Error al aceptar el socket\n");
            return -1;
        }

        pid_t pid = fork();
        
        if(pid < 0){
            perror("Error en el fork");
            return -1;
        }
        else if (pid == 0){//hijo
            char buff[BUFFER + 1];
        
            int respuesta = getnameinfo((struct sockaddr *)&client_addr, client_addrlen, host,  NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            if(respuesta == -1){
                perror("Error al adquirir la informacion del cliente\n");
            }

            printf("Conexión desde %s:%s\n", host, serv);

            while(1){
                size_t recieve = recv(cliente, buff, BUFFER, 0);
                if (recieve == -1){
                    perror("Error al recibir el mensaje\n");
                    return -1;
                }
                else if(recieve == 0){
                    break;
                }

                if(send(cliente, buff,strlen(buff), 0) == -1){
                    perror("Error al responder al cliente\n");
                    return -1;
                }

                memset(buff, 0, BUFFER);
            }
            printf("FIN\n");
        }
        else{//padre
            close(cliente);
        }
    }
    return 0;
}



/*
dos terminales 
netcat
ss -uan*/