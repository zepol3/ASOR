
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define BUF_SIZE 500

int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];
    if (argc != 3) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    /* getaddrinfo() returns a list of address structures.
    Try each address until we successfully bind(2).
    If socket(2) (or bind(2)) fails, we (close the socket
    and) try the next address. */

    sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1){
        perror("error al crear el socket");
        return -1;
    }
    if (bind(sfd, result->ai_addr, result->ai_addrlen) != 0){
        perror("error al asociar el socket");
        close(sfd);
        return -1;
    }

    freeaddrinfo(result);           /* No longer needed */
    /* Read datagrams and echo them back to sender */
    for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
        continue;               /* Ignore failed request */
        char host[NI_MAXHOST], service[NI_MAXSERV], respusesta[BUF_SIZE];
        s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        if (s == 0)
            printf("Received %zd bytes from %s:%s\n", nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

        strcpy(respusesta, host);
        int l = strlen(respusesta);
        respusesta[l] = '\n';
		respusesta[l + 1] = '\0';

        if (sendto(sfd, respusesta, l + 2, 0, (struct sockaddr *) &peer_addr, peer_addr_len) == -1)
            fprintf(stderr, "Error sending response\n");
    }
}
