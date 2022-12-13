
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

int main(int argc, char *argv[]){
    
    if(argc < 3){
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

    if (bind(sockett, resultado->ai_addr, resultado->ai_addrlen) != 0) {
        perror("Error al ejecutar el bind\n");
        return -1;
    }

    freeaddrinfo(resultado);

    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

    size_t l;
    time_t tiempo;
    char buff[BUFFER + 1];
    size_t tiempo_bytes;
	struct tm *tm;
	char mensage[MESSAGE + 1];

    while(1){
        l = recvfrom(sockett, buff, BUFFER, 0, (struct sockaddr *) &client_addr, &client_addrlen);
		buff[l - 1] = '\0';

        getnameinfo((struct sockaddr *) &client_addr, client_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        printf("hemos recibido %ld bytes de %s por el puerto %s\n", l, host, serv);

        tiempo = time(NULL);
        tm = localtime(&tiempo);

        if(buff[0] == 't'){
            
			tiempo_bytes = strftime(mensage, MESSAGE, "%T", tm);
			mensage[tiempo_bytes] = '\n';
			mensage[tiempo_bytes + 1] = '\0';
			
			if (sendto(sockett, mensage, tiempo_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
			{
				printf("sendto()\n");
				return -1;
			}
        }

        else if(buff[0] == 'd'){
            tiempo_bytes = strftime(mensage, MESSAGE, "%F", tm);
			mensage[tiempo_bytes] = '\n';
			mensage[tiempo_bytes + 1] = '\0';
			
			if (sendto(sockett, mensage, tiempo_bytes + 2, 0, (struct sockaddr *) &client_addr, client_addrlen) == -1)
			{
				printf("sendto()\n");
				return -1;
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

    return 0;
}



/*
dos terminales 
netcat
ss -uan*/