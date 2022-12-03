
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/*VERSION SYSTEM*/
int main(int argc, char **argv){

       if(argc < 2){
              perror("Numero invalido de argumentos\n");
              return -1;
       }
       //concateno las entradas de argv desde [1] en adelante y eso se lo paso a system
       int tam = 0;
       for(int x = 0; x < argc; x++){
              tam += strlen(argv[x]);
       }

       char comando[tam];
       sprintf(comando,"%s",argv[1]);
       for(int x = 2; x < argc; x++){
              sprintf(comando, "%s %s", comando, argv[x]);
       }
       if(system(comando) == -1){
              perror("Error en system  al ejecutar el comando");
              return -1;
       }
       printf("El comando terminó de ejecutarse\n");
       return 0;
}

/*ps -el y "ps -el"  tienen el mismo output*/
/*OUTPUT ps -el
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ gcc -o E7-s E7-SYSTEM.c
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ./E7-s ps -el
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0     1     0  0  80   0 -   450 -      ?        00:00:48 init
5 S     0     9     1  0  80   0 -   224 -      ?        00:00:00 init
1 S     0    10     9  0  80   0 -   224 -      ?        00:00:00 init
4 S  1000    11    10  0  80   0 -  2575 do_wai pts/0    00:00:00 bash
5 S     0  6439     1  0  80   0 -   427 -      ?        00:00:00 init
1 S     0  6440  6439  0  80   0 -   427 -      ?        00:00:00 init
4 S  1000  6441  6440  0  80   0 -  2510 do_wai pts/1    00:00:00 bash
0 S  1000 13226  6441  0  80   0 -  2236 do_wai pts/1    00:00:00 man
0 S  1000 13236 13226  0  80   0 -  1900 -      pts/1    00:00:00 pager
0 S  1000 13610    11  0  80   0 -   590 do_wai pts/0    00:00:00 E7-s
0 S  1000 13611 13610  0  80   0 -   653 do_wai pts/0    00:00:00 sh
0 R  1000 13612 13611  0  80   0 -  2630 -      pts/0    00:00:00 ps
El comando terminó de ejecutarse*/
/*OUTPUT “ps -el”
alvaro@PORTATIL-ALVARO:~/ASOR/Practica 2-3$ ./E7-s "ps -el"
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
4 S     0     1     0  0  80   0 -   450 -      ?        00:00:49 init
5 S     0     9     1  0  80   0 -   224 -      ?        00:00:00 init
1 S     0    10     9  0  80   0 -   224 -      ?        00:00:00 init
4 S  1000    11    10  0  80   0 -  2575 do_wai pts/0    00:00:00 bash
5 S     0  6439     1  0  80   0 -   427 -      ?        00:00:00 init
1 S     0  6440  6439  0  80   0 -   427 -      ?        00:00:00 init
4 S  1000  6441  6440  0  80   0 -  2510 do_wai pts/1    00:00:00 bash
0 S  1000 13226  6441  0  80   0 -  2236 do_wai pts/1    00:00:00 man
0 S  1000 13236 13226  0  80   0 -  1900 -      pts/1    00:00:00 pager
0 S  1000 13904    11  0  80   0 -   590 do_wai pts/0    00:00:00 E7-s
0 S  1000 13905 13904  0  80   0 -   653 do_wai pts/0    00:00:00 sh
0 R  1000 13906 13905  0  80   0 -  2630 -      pts/0    00:00:00 ps
El comando terminó de ejecutarse*/


/*
resumen:
system() crea un proceso hijo con el comando que le pasemos
execvp() sustituye el proceso actual por el del comando que pasemos


SYSTEM(3)                     Linux Programmer's Manual                    SYSTEM(3)

NAME
       system - execute a shell command

SYNOPSIS
       #include <stdlib.h>

       int system(const char *command);

DESCRIPTION
       The system() library function uses fork(2) to create a child process that ex‐
       ecutes the shell command specified in command using execl(3) as follows:

           execl("/bin/sh", "sh", "-c", command, (char *) NULL);

       system() returns after the command has been completed.

       During execution of the command, SIGCHLD will  be  blocked,  and  SIGINT  and
       SIGQUIT  will be ignored, in the process that calls system().  (These signals
       will be handled according to their defaults inside the child process that ex‐
       ecutes command.)

       If command is NULL, then system() returns a status indicating whether a shell
       is available on the system.

RETURN VALUE
       The return value of system() is one of the following:

       *  If command is NULL, then a nonzero value if a shell is available, or 0  if
          no shell is available.

       *  If  a  child  process could not be created, or its status could not be re‐
          trieved, the return value is -1 and errno is set to indicate the error.

       *  If a shell could not be executed in the child  process,  then  the  return
          value is as though the child shell terminated by calling _exit(2) with the
          status 127.

       *  If all system calls succeed, then the return value is the termination sta‐
          tus  of  the child shell used to execute command.  (The termination status
          of a shell is the termination status of the last command it executes.)

       In the last two cases, the return value is a "wait status" that can be  exam‐
       ined using the macros described in waitpid(2).  (i.e., WIFEXITED(), WEXITSTA‐
       TUS(), and so on).

       system() does not affect the wait status of any other children.



EXEC(3)                       Linux Programmer's Manual                      EXEC(3)

NAME
       execl, execlp, execle, execv, execvp, execvpe - execute a file

SYNOPSIS
       #include <unistd.h>

       extern char **environ;

       int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL );
       int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL );
       int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] );
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);

DESCRIPTION
       The  exec() family of functions replaces the current process image with a new
       process image.  The functions described in this manual  page  are  front-ends
       for  execve(2).  (See the manual page for execve(2) for further details about
       the replacement of the current process image.)

       The initial argument for these functions is the name of a file that is to  be
       executed.
RETURN VALUE
       The exec() functions return only if an error has occurred.  The return  value
       is -1, and errno is set to indicate the error.

*/