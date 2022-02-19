#include <stdio.h>

int main() 

{
	int base; 
	int exp; 
	printf("-------------------------------------------\n");
	printf("Mostrar a^n:\n\n");

	printf("Ingresar numero base a: ");
    scanf("%d", &base); 
	printf("Ingresar exponente n: ");
  	scanf("%d", &exp); 

    int x, res = 1;
    for (x = 0; x < exp; x++){
        res *= base;
	}
	printf("\nResultado = %d\n\n", res);
	printf("-------------------------------------------\n\n");

 }
