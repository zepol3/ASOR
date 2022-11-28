
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>


int main(){
    
    char *politica;
    int policy, min, max, priority;
    /*
    sched_getparam() retrieves the scheduling parameters for the
    thread identified by pid.  If pid is zero, then the parameters of
    the calling thread are retrieved.
    */
    
    policy = sched_getscheduler(getpid());
    min  = sched_get_priority_min(policy);
    max = sched_get_priority_min(policy);
    priority = getpriority(PRIO_PROCESS, 0);

    switch (policy)
    {
    case SCHED_OTHER:
        politica = "OTHER";
        break;
    
    case SCHED_FIFO:
        politica = "FIFO";
        break;
    
    case SCHED_RR:
        politica = "RR";
        break;
    
    
    default:
        politica = "DESCONOCIDA";
        break;
    }

    printf("Politica: %s\n",politica);
    printf("min: %d\n",min);
    printf("max: %d\n",max);
    printf("priority: %d\n",priority);
    return 0;
}