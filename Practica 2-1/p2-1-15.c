#include <time.h>
#include <stdio.h>
#include <locale.h>


int main()
{
	char str[128];
	const size_t m = 100;
	const char *format = "%A, %d de %B de %Y, %H:%M";/*En mayuscula para que salga en formato completo, si no se acorta*/

	setlocale(LC_ALL, "es_ES");
	
	time_t t = time(NULL);
	struct tm * lt = localtime(&t);
	
	size_t l = strftime(str, m, format, lt);

	printf("%s\n", str);

	return 0;
}