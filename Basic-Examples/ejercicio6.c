#include <stdio.h>
#include <string.h>
 
int main()
{
  	char cad[100], letra;
  	int x, y;
  	y = 0;
    
    printf("-------------------------------------------\n\n");
  	printf("Ingresar cadena:\n");
  	gets(cad);
  	
  	printf("Ingresar caracter a buscar:\n");
  	scanf("%c", &letra);
  	
  	for(x = 0; x <= strlen(cad); x++)
  	{
  		if(cad[x] == letra)  
		{
  			y++;
			break;    	
 		}
	}
    if(y == 0)
  	{
  		printf("No se encontró el elemento");
	}
	else
	{
		printf("El elemento '%c' aparece por primera vez en la pos %d ", letra, x + 1);
	}	

    printf("\n\n-------------------------------------------\n\n");
  	return 0;
}