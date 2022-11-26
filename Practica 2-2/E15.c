
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc,char **argv){
    
    char buff[1024];
    struct flock lock;
    time_t time;
    struct tm *tm;

    if(argc != 2){
        perror("Numero invalido de argumentos\n");
        return -1;
    }

    int file = open(argv[1], O_CREAT| O_RDWR, S_IRUSR|S_IWUSR);
    if(file == -1){
        perror("Error al abrir el achivo\n");
        return -1;
    }
    
    if (fcntl(file, F_GETLK, &lock) == -1){
        /*
        F_GETLK: Comprueba si se puede activar el cerrojo descrito en lock:
            -Si se puede activar, establece el campo l_type de lock a F_UNLCK
            -Si no, devuelve en lock los detalles de uno de los cerrojos que lo impiden, incluyendo el PID del proceso que lo mantiene
        */
        perror("Error al coger el lock");
        close(file);
        return -1;
    }

    printf("cerrojo creado correctamente");

    if(lock.l_type == F_UNLCK){
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();

        if (fcntl(file, F_SETLK, &lock) == -1){
            /*
            F_SETLK: Activa (si l_type es F_WRLCK o F_RDLCK) o libera (si l_type es F_UNLCK) el cerrojo descrito por lock
                -Si hay un cerrojo incompatible, devuelve -1 con errno=EAGAIN
            */
            perror("Error al activar el lock");
            close(file);
            return -1;
        }

        printf("cerrojo acrivado correctamente");

        time = time(NULL);
        tm = localtime(&time);
        strftime( buff, sizeof(buff), "Fecha actual: %d/%m/%Y %H:%M:%S\n", tm);
        write(file, &buff, strlen(buff));
        sleep(10);

        lock.l_type = F_UNLUCK;

        if (fcntl(file, F_SETLKW, &lock) == -1){
            /*
            F_SETLKW: Igual que F_SETLK, pero
                Si hay un cerrojo incompatible, espera a que sea liberado
            */
            perror("Error al liberar el lock");
            close(file);
            return -1;
        }
        else{
            printf("cerrojo liberado correctamente, voy a dormir");
            sleep(10);
            close(file);
        }
    }
    else{
        perror("Error al bloquear el fichero");
        close(file);
        return -1;
    }
    return 0;
}