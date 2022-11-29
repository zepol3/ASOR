
#include <unistd.h>
#include <stdlib.h>


/*VERSION SYSTEM*/
int main(int argcn char **argv){

       if(argc < 2){
              perror("Numero invalido de argumentos\n");
              return -1;
       }
       //concateno las entradas de argv desde [1] en adelante y eso se lo paso a system
       int system(argv);

       return 0;
}







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