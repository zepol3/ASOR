
#include <signal.h>
#include <stddef.h>
#include <stdio.h>

volatile int contSIGTSTP = 0;
volatile int contSIGINT = 0;
void handler(int senal)
{
    if (senal == SIGINT)
        contSIGINT++;
    if (senal == SIGTSTP)
        contSIGTSTP++;
}

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("error en sigint\n");
        return -1;
    }
    if (sigaction(SIGTSTP, &sa, NULL) == -1)
    {
        perror("error en sigint\n");
        return -1;
    }

    sigset_t set;
    sigemptyset(&set);

    while ((contSIGINT + contSIGTSTP) < 10)
    {
        sigsuspend(&set);
    }

    printf("contSIGINT: %d\n", contSIGINT);
    printf("contSIGTSTP: %d\n", contSIGTSTP);

    return 0;
}