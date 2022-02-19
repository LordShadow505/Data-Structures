#include <stdio.h>

int main() 

{
	int x = 1, y = 0, i;
	int lim;
	printf("-------------------------------------------\n");
	printf("Mostrar Serie de Fibonacci:\n\n");
	printf("Ingresa cuántas sucesiones mostrar:\n");
	scanf("%d", &lim); //se muestra el doble ingresado
	printf("\n");
	for(i = 0; i < lim; i++){
		printf("%d\n", y);
		printf("%d\n", x);
		y = y + x;
		x = x + y;
	}
	printf("\n\n-------------------------------------------\n");
	
}
