
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*VERSION EXECVP*/
int main(int argc, char **argv){

    if(argc < 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }
    if(execvp(argv[1], argv +1) == -1){
        perror("Error en execvp al ejecutar el comando");
        return -1;
    }
    printf("El comando terminó de ejecutarse\n");
    return 0;
}

/*OUTPUT ps -el
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ./E7-e ps -el
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0     1     0  0  80   0 -   452 -      ?        00:00:56 init
5 S     0     9     1  0  80   0 -   224 -      ?        00:00:00 init
1 R     0    10     9  0  80   0 -   224 -      ?        00:00:00 init
4 S  1000    11    10  0  80   0 -  2575 do_wai pts/0    00:00:00 bash
5 S     0  6439     1  0  80   0 -   427 -      ?        00:00:00 init
1 S     0  6440  6439  0  80   0 -   427 -      ?        00:00:00 init
4 S  1000  6441  6440  0  80   0 -  2510 do_wai pts/1    00:00:00 bash
0 S  1000 14315  6441  0  80   0 -  2235 do_wai pts/1    00:00:00 man
0 S  1000 14325 14315  0  80   0 -  1932 -      pts/1    00:00:00 pager
0 R  1000 16016    11  0  80   0 -  2630 -      pts/0    00:00:00 ps*/
/*OUTPUT "ps -el"
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ./E7-e "ps -el"
Error en execvp al ejecutar el comando: No such file or directory
*/