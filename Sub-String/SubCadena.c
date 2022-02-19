// EXTRAE UNA SUBCADENA DE UNA CADENA
#include <stdio.h>

void Muestra(char*, int, int);

int main()
{
	char *RENG = "Parangaritirimucuaro";

	Muestra(RENG, 5, 20);
}


void Muestra(char *CAD, int Desde, int Hasta)
{
	int Indice = 0;

	for(Indice = Desde; Indice <= Hasta; Indice++)
		printf("%c", CAD[Indice]);
	printf("\n");
}
