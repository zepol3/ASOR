
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

#define BUFFER 2
#define MESSAGE 128
#define LISTEN_BACKLOG 50

void handler(int senal){
    wait(NULL);
}

int main(int argc, char *argv[]){
    
    if(argc < 3){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);

    struct sigaction sig;
    sig.sa_handler = handler;

    if(sigaction(SIGTERM , &sig, NULL) == -1){
        perror("error al cambiarl el controlador para SIGTERM ");
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

    if (bind(sockett, resultado->ai_addr, resultado->ai_addrlen) != 0) {
        perror("Error al ejecutar el bind\n");
        return -1;
    }

    if(listen(sockett, LISTEN_BACKLOG) == -1){
        perror("error en el listen\n");
        return -1;
    }

    freeaddrinfo(resultado);

    while(1){///cuantas veces tengo que ejecutar esto??
        pid_t pid = fork();
        
        if(pid < 0){
            perror("Error en el fork");
            return -1;
        }
        else if (pid == 0){//hijo

            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];

            struct sockaddr_storage client_addr;
            socklen_t client_addrlen = sizeof(client_addr);

            if(accept(sockett, (struct sockaddr *) &client_addr, &client_addrlen) == -1){
                perror("Error al aceptar al hijo %s\n", getpid());
                return -1;
            }

            size_t l;
            time_t tiempo;
            char buff[BUFFER + 1];
            size_t tiempo_bytes;
            struct tm *tm;
            char mensage[MESSAGE + 1];

            fd_set selector;

            while(1){
                FD_ZERO(&selector);//inicializo el selector a vacio
                FD_SET(0, &selector); //inluyo stdin en el selector
                FD_SET(sockett, &selector);//incluyo el socket en el selector
                if(select(sockett + 1, &selector, NULL, NULL, NULL) == -1){
                    perror("error al abrir el select\n");
                    return -1;
                }
                if(FD_ISSET(0, &selector)){//si el selector esta apuntando a stdin
                    int leidos = read(0, buff, BUFFER);
                    printf("hemos recibido %d bytes por stdin\n", leidos);
                }
                else{//si el selector esta apuntando al socket
    
                    l = recvfrom(sockett, buff, BUFFER, 0, (struct sockaddr *) &client_addr, &client_addrlen);
                    buff[l - 1] = '\0';

                    getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                    printf("hemos recibido %ld bytes de %s por el puerto %s, pid Hijo = %s\n", l, host, serv, getpid());
                }

                tiempo = time(NULL);
                tm = localtime(&tiempo);

                if(buff[0] == 't'){
                    
                    tiempo_bytes = strftime(mensage, MESSAGE, "%T", tm);
                    mensage[tiempo_bytes] = '\n';
                    mensage[tiempo_bytes + 1] = '\0';
                    
                    if(FD_ISSET(0, &selector)){
                        printf("%s\n", mensage);
                    }
                    else{
                        if(connect(sockett, (struct sockaddr *) &client_addr, &client_addrlen) == -1){
                            perror("error al conectar con el socket en t");
                            return -1;
                        }
                        if (sendto(sockett, mensage, tiempo_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
                        {
                            printf("sendto()\n");
                            return -1;
                        }
                    }
                }

                else if(buff[0] == 'd'){
                    tiempo_bytes = strftime(mensage, MESSAGE, "%F", tm);
                    mensage[tiempo_bytes] = '\n';
                    mensage[tiempo_bytes + 1] = '\0';
                    if(FD_ISSET(0, &selector)){
                        printf("%s\n", mensage);
                    }
                    else{
                        if(connect(sockett, (struct sockaddr *) &client_addr, &client_addrlen) == -1){
                            perror("error al conectar con el socket en t");
                            return -1;
                        }
                        if (sendto(sockett, mensage, tiempo_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
                        {
                            printf("sendto()\n");
                            return -1;
                        }
                    }
                }

                else if(buff[0] == 'q'){
                    printf("Saliendo...\n");
                    
                    return 0;
                }
                else{
                    printf("comando no valido\n");
                }
    }
        }
        else{//padre

        }
    }
   

    return 0;
}



/*
dos terminales 
netcat
ss -uan*/