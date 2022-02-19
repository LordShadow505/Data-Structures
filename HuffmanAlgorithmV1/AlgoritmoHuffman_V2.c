#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//======================================================================

//Carlos Alberto Tavera Arteaga - 1628839A
//Algoritmo de Huffman

//======================================================================






//======================================================================
//Nodos
//======================================================================

typedef struct Nodo_t {
	struct Nodo_t *left, *right;
	int frecu;
	char c;
}*node;
 
struct Nodo_t pool[256] = {{0}};
node qqq[255], *q = qqq - 1;
int nodo_n = 0, fin_q = 1;
char *code[128] = {0}, memoria[1024];


node Nodo_Nuevo(int frecu, char c, node a, node b)
{
	node n = pool + nodo_n++;
	if (frecu) n->c = c, n->frecu = frecu;
	else {
		n->left = a, n->right = b;
		n->frecu = a->frecu + b->frecu;
	}
	return n;
}
 

void Insertar_q(node n)
{
	int j, i = fin_q++;
	while ((j = i / 2)) {
		
		if (q[j]->frecu <= n->frecu) break;
		q[i] = q[j], i = j;
	}
	q[i] = n;
}

node Borrar_q()
{
	int i, l;
	node n = q[i = 1];
 
	if (fin_q < 2) return 0;
	fin_q--;
	while ((l = i * 2) < fin_q) {
		if (l + 1 < fin_q && q[l + 1]->frecu < q[l]->frecu) l++;
		q[i] = q[l], i = l;
	}
	q[i] = q[fin_q];
	return n;
}
//======================================================================








//======================================================================
//Constructor
//======================================================================

void Constructor(node n, char *s, int len)
{
	static char *out = memoria;
		if (n->c) {
			s[len] = 0;
			strcpy(out, s);
			code[n->c] = out;
			out += len + 1;
			return;
		}
 
	s[len] = '0'; Constructor(n->left,  s, len + 1);
	s[len] = '1'; Constructor(n->right, s, len + 1);

}
//======================================================================








//======================================================================
//Inicializador
//======================================================================

void Iniciar(const char *s)
{
	int i, frecu[128] = {0};
	char c[16];
 
	
	while (*s) frecu[(int)*s++]++;
 
	
		for (i = 0; i < 128; i++) {
			if (frecu[i]) Insertar_q(Nodo_Nuevo(frecu[i], i, 0, 0));
		}
	
	
	while (fin_q > 2) {
		Insertar_q(Nodo_Nuevo(0, 0, Borrar_q(), Borrar_q()));
	}
 
	
	Constructor(q[1], c, 0);
}
//======================================================================








//======================================================================
//Función Codificar y Decodificar
//======================================================================

void Codificar(const char *s, char *out)
{
	while (*s) {
		strcpy(out, code[*s]);
		out += strlen(code[*s++]);
	}
}
 
void Decodificar(const char *s, node t)
{
	node n = t;
	while (*s) {
		if (*s++ == '0') n = n->left;
		else n = n->right;
 
		if (n->c) putchar(n->c), n = t;
	}
 
	putchar('\n');
	if (t != n) printf("ERROR\n");
}
//======================================================================








//======================================================================
//Función Empaquetar en Bytes y Hexadecimal
//======================================================================

void Empaquetar(char *cad)
{
	
	
	int i = 0;
	int lim = 8;
	int cont = 0;

	if ( !cad[0] ) return;

	int longitud = strlen(cad);
	
	for ( cont = 0; cont < 8; i++ )
	{
		//Imprime un espacio cada 8 caracteres
		if ( i == lim )
		{
			lim += 8;
			
			printf(" ");

		}

		//Se detiene cuando el contador llega a 8 y
		//se comprueba que los paquetes son bytes
		if ( i == longitud){
			cont = 8;

			//Comprobar bytes
			if(longitud%8!=0){
				for (int j = 0; j < 8-longitud%8; j++)
				{
					printf("0");
				}
			}
			
		}
		
		//Imprime caracter a caracter
		printf("%c", cad[i]);
		
		
	}
	
	

}

void EmpaquetarHex()
{
	
	char texto[1024];
	scanf("%c", texto);
	scanf("%[^\n]", texto);
    char delimitador[] = " ";
    char *token = strtok(texto, delimitador);
   
    
    if(token != NULL){
		printf("\nMensaje empaquetado en Hex:\n"); 
	    char *a = token;
	    int num = 0;

        while(token != 0){
            int num = 0;
            do {
             int b = *a=='1'?1:0;
             num = (num<<1)|b;
             a++;} while (*a);

            
            printf("0x%X ", num);

            token= strtok(NULL, delimitador);
		}
	}

	
	
}
//======================================================================




	


//======================================================================
//Función Main
//======================================================================

int main(void)
{

	printf("\n\n==============================================================\n");

    printf("Carlos Alberto Tavera Arteaga - 1628839A\n");
	printf("Algoritmo de Codificacion y Decodificacion\n");

	printf("==============================================================\n\n");
	
	
	//Quitar los comentarios para elegir el modo:
	
    //===================================================
	//MODO MANUAL:
	/*
	printf("\n--------------------------------------------------\n");
	char cadena[1024];
	printf("Ingresar el mensaje a codificar:\n");
	scanf("%[^\n]", cadena);
	const char *str = cadena; //Cadena a Codificar
	printf("--------------------------------------------------\n");
	*/
	//===================================================


	//===================================================
	//MODO AUTOMATICO (PARA HACER PRUEBAS RAPIDO):

	const char *str = "ata la jaca a la estaca"; //Cadena a Codificar

	//===================================================





	char memoria[1024]; 
	int i;
	

	Iniciar(str);

	//Letras Codificadas
	printf("\n--------------------------------------------------\n");
	printf("Letras codificadas:\n%s", memoria);
	for (i = 0; i < 128; i++) 
		if (code[i]) printf("'%c': %s\n", i, code[i]);
	printf("--------------------------------------------------\n");


	//Iniciar Codificador
	printf("\n--------------------------------------------------");
	Codificar(str, memoria);
	printf("\nMensaje codificado:\n%s\n", memoria);
	printf("--------------------------------------------------\n");	


	//Empaquetar en Bytes
	printf("\n--------------------------------------------------");
	printf("\nMensaje empaquetado en bytes:\n");
	Empaquetar(memoria);
	printf("\n\n--------------------------------------------------\n");
	


	//Iniciar Decodificador
	printf("\n--------------------------------------------------");
	printf("\nMensaje decodificado:\n");
	Decodificar(memoria, q[1]);
	printf("--------------------------------------------------\n");


	//Empaquetar en cadena Hexadecimal
	int opc;
	printf("\n--------------------------------------------------");
	printf("\nQuieres empaquetar el mensaje en Hex?:\n"); 
	printf("1. Si        2.No\n\n");
	scanf ("%d", &opc);
  	
	
		switch (opc){
  	
  			case 1:
			printf("\nCopiar el mensaje empaquetado para convertir en Hex:\n");
			EmpaquetarHex();
			printf("\n--------------------------------------------------\n"); 
    			break;
   
			default:
			printf("\nSaliendo...\n");
			printf("--------------------------------------------------\n");
   			break;
  			}	
	
	

	printf("\n==============================================================\n\n");
 
	return 0;
}
