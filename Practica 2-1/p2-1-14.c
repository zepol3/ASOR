#include <stdio.h>
#include <time.h>

int main()
{
	time_t t = time(NULL);
	struct tm *dInfo = localtime(&t);
	
	printf("Estamos en el año: %d\n", 1900+dInfo->tm_year); /*nos da 122(tm_year) lo cual tenemos que sumarle 1900 */

	return 0;
}