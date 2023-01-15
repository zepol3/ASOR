#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFER 256

int main()
{

    int tub1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
    if (tub1 == -1)
    {
        perror("error al abrir al tuberia1\n");
        return -1;
    }

    int tub2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
    if (tub2 == -1)
    {
        perror("error al abrir al tuberia2\n");
        return -1;
    }

    fd_set rfds;
    int max;
    /* Watch stdin (fd 0) to see when it has input. */

    while (1)
    {
        FD_ZERO(&rfds);
        FD_SET(tub1, &rfds);
        FD_SET(tub2, &rfds);
        if (tub1 > tub2)
            max = tub1 + 1;
        else
            max = tub2 + 1;
        if (select(max, &rfds, NULL, NULL, NULL) == -1)
        {
            perror("Error al selccionar\n");
            return -1;
        }

        char buff[BUFER] = {0};
        ssize_t tam = BUFER + 1;

        if (FD_ISSET(tub1, &rfds))
        {
            while (tam == (BUFER + 1))
            {
                tam = read(tub1, buff, BUFER);
                printf("Tuberia 1: %s", buff);
            }
            if (tam != 256)
            {
                close(tub1);
                tub1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
                if (tub1 == -1)
                {
                    perror("error al abrir al tuberia1\n");
                    close(tub1);
                    close(tub2);
                    return -1;
                }
            }
        }
        else if (FD_ISSET(tub2, &rfds))
        {
            while (tam == (BUFER + 1))
            {
                tam = read(tub2, buff, BUFER);
                printf("Tuberia 2: %s", buff);
            }
            if (tam != 256)
            {
                close(tub2);
                tub2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
                if (tub2 == -1)
                {
                    perror("error al abrir al tuberia2\n");
                    close(tub1);
                    close(tub2);
                    return -1;
                }
            }
        }
    }

    close(tub1);
    close(tub2);
    return 0;
}