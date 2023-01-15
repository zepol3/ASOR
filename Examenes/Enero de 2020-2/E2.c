
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

#define BUF_SIZE 500
#define LISTEN_BACKLOG 50

int  main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];

    if (argc < 3) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        return -1;
    }

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }
    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully bind(2).
        If socket(2) (or bind(2)) fails, we (close the socket
        and) try the next address. */
    
    sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1){
        perror("Error al crear socket\n");
        return -1;
    }
    if (bind(sfd, result->ai_addr, result->ai_addrlen) != 0){
        perror("Error al crear socket\n");
        return -1;
    }
    
    freeaddrinfo(result);           /* No longer needed */
    
    if(listen(sfd, LISTEN_BACKLOG) == -1){
        perror("Error en listen\n");
        return -1;
    }

    peer_addr_len = sizeof(struct sockaddr_storage);
    int cliente = accept(sfd,(struct sockaddr *)&peer_addr, &peer_addr_len);
    if( cliente == -1){
        perror("Error en listen\n");
        return -1;
    }

    /* Read datagrams and echo them back to sender */

    for (;;) {
        
        nread = recv(cliente, buf, BUF_SIZE, 0);
        if (nread == -1){
            perror("Error al recibir");
            return -1;
        }
        else if(nread == 0)
            break;
        char host[NI_MAXHOST], service[NI_MAXSERV]; 
        s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
        if (s == 0)
            printf("Received %zd bytes from %s:%s\n", nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s)); 
        if (send(cliente, buf, nread, 0) != nread)
            fprintf(stderr, "Error sending response\n");
    }
}