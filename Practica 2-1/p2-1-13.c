#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define MAX 1000000

int main()
{
	int n = 0;
	struct timeval iniTime, finTime;
	
	gettimeofday(&iniTime, NULL);
	for (int i = 0; i < MAX; i++)
	{
		n++;
	}
	gettimeofday(&finTime, NULL);

	suseconds_t tiempoTotalSec = finTime.tv_usec - iniTime.tv_usec;
	printf("Tiempo total en microsegundos: %ld\n", tiempoTotalSec);
	
	return 0;
}