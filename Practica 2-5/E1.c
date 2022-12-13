
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]){
    
    if(argc < 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }


    struct addrinfo hints;
    struct addrinfo *resultado;
    struct addrinfo *contador;
    
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int s = getaddrinfo(argv[1], NULL, &hints, &resultado);

    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }

    char host[NI_MAXHOST];

    for(contador = resultado; contador!= NULL; contador = contador->ai_next){
		/* Obtener la información a partir del host numérico. */
		getnameinfo(contador->ai_addr, contador->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		printf("Dirección: %s (familia %d; tipo %d)\n", host, contador->ai_family, contador->ai_socktype);
	}

	freeaddrinfo(resultado);
    return 0;
}
/*
GETADDRINFO(3)                                Linux Programmer's Manual                                GETADDRINFO(3)

NAME
       getaddrinfo, freeaddrinfo, gai_strerror - network address and service translation

SYNOPSIS
       #include <sys/types.h>
       #include <sys/socket.h>
       #include <netdb.h>

       int getaddrinfo(const char *node, const char *service,
                       const struct addrinfo *hints,
                       struct addrinfo **res);

       void freeaddrinfo(struct addrinfo *res);

       const char *gai_strerror(int errcode);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       getaddrinfo(), freeaddrinfo(), gai_strerror():
           Since glibc 2.22: _POSIX_C_SOURCE >= 200112L
           Glibc 2.21 and earlier: _POSIX_C_SOURCE

DESCRIPTION
       Given  node  and service, which identify an Internet host and a service, getaddrinfo() returns one or more ad‐
       drinfo structures, each of which contains an Internet address that can be specified in a call  to  bind(2)  or
       connect(2).   The  getaddrinfo() function combines the functionality provided by the gethostbyname(3) and get‐
       servbyname(3) functions into a single interface, but unlike the latter functions, getaddrinfo()  is  reentrant
       and allows programs to eliminate IPv4-versus-IPv6 dependencies.

       The addrinfo structure used by getaddrinfo() contains the following fields:

           struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };
           The  hints  argument  points to an addrinfo structure that specifies criteria for selecting the socket address
       structures returned in the list pointed to by res.  If hints is not NULL it points to  an  addrinfo  structure
       whose ai_family, ai_socktype, and ai_protocol specify criteria that limit the set of socket addresses returned
       by getaddrinfo(), as follows:

       ai_family   This field specifies the desired address family for the returned addresses.  Valid values for this
                   field  include  AF_INET and AF_INET6.  The value AF_UNSPEC indicates that getaddrinfo() should re‐
                   turn socket addresses for any address family (either IPv4 or IPv6, for example) that can  be  used
                   with node and service.

       ai_socktype This field specifies the preferred socket type, for example SOCK_STREAM or SOCK_DGRAM.  Specifying
                   0 in this field indicates that socket addresses of any type can be returned by getaddrinfo().

       ai_protocol This field specifies the protocol for the returned socket addresses.  Specifying 0 in  this  field
                   indicates that socket addresses with any protocol can be returned by getaddrinfo().

       ai_flags    This field specifies additional options, described below.  Multiple flags are specified by bitwise
                   OR-ing them together.

       All the other fields in the structure pointed to by hints must contain either 0 or a null pointer,  as  appro‐
       priate.

*/



/*SALIDA

alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-5$ gcc -o E1 E1.c
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-5$ ./E1 www.google.es
Dirección: 142.250.200.67 (familia 2; tipo 1)
Dirección: 142.250.200.67 (familia 2; tipo 2)
Dirección: 142.250.200.67 (familia 2; tipo 3)
Dirección: 2a00:1450:4003:80d::2003 (familia 10; tipo 1)
Dirección: 2a00:1450:4003:80d::2003 (familia 10; tipo 2)
Dirección: 2a00:1450:4003:80d::2003 (familia 10; tipo 3)
*/