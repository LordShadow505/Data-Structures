#include <stdio.h>

int main() 

{

    int x, y, num = 0;
    printf("-------------------------------------------\n\n");
    printf("Ingresar numero: ");
    scanf("%d", &x);

     for (y = 2; y <= x/2; ++y) {
         if (x % y == 0) {
         num = 1;
      break;
         }
     }

     if (x == 1) {
    printf("\n1 es la unidad");
     } 
    else {
    if (num == 0)
      printf("\n%d Es primo.", x);
    else
      printf("\n%d No es primo", x);
     }
    printf("\n\n-------------------------------------------\n\n");
  return 0;
}

 
  
