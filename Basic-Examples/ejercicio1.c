#include <stdio.h>

int main() 

{
	int x, y;
	int f=1;
	printf("-------------------------------------------\n");
	printf("Calculadora de factoriales:\n\n");
	printf("\nIngresa un número:\n");
	scanf("%d", &x);

	for (y = x; y > 1; y--){
	f = f*y;
	}

	printf("= %d\n\n", f);
	printf("-------------------------------------------");
	
}