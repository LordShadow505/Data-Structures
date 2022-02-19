#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//======================================================================

//Carlos Alberto Tavera Arteaga - 1628839A
//Algoritmo de Huffman

//======================================================================


//======================================================================
//	Nodos y "Libreria" de Funciones
//======================================================================

#define MAX	1000 //Maximo de caracteres

struct codigo{ 
	char letra;
	char *x;
	struct codigo *siguiente;
};

struct nodo{ 
	char letra;
	int contador;
	struct nodo *siguiente;
	struct nodo *izquierda;
	struct nodo *derecha;
};

int Longitud(struct nodo *nodo);

void ImprimirCod(struct codigo *nodo);
void ImprimirLista(struct nodo *cabeza);
void AsignaCodigo(struct nodo *nodo,struct codigo **codigoref,char *x,int y);

void Organiza(struct nodo *a[],int longitud);
void OrganizaFreq(struct nodo **cabezaref);
void OrganizaInserta(struct nodo **cabezaref,struct nodo *nodo_n);

void ConstruyeArbol(struct nodo **cabezaref);

char *Copia(char *s,int Indice,char letra);
void Cambia(struct nodo *a[],int i,int j);
char *Codifica(char *Cadena,struct codigo *codigo);
char *returnCodigo(struct codigo *nodo,char m);
void Mueve(struct codigo **codigoref,char *x,char letra);
void Separa(struct nodo *cabeza,struct nodo **aref,struct nodo **bref);

struct nodo *Frecuencia(struct nodo *p, char letra);
struct nodo *CombinaNodo(struct nodo *ultimos2);
struct nodo *Adjunta(struct nodo *a,struct nodo *b);


void Empaquetar(char *eCadena);
void EmpaquetarHex(char *eCadena);


//======================================================================








//======================================================================
//	Funcion Principal
//======================================================================
//  Esta función es el centro de control que ejecuta las demas funciones
//======================================================================

int main()
{
	
	printf("\n\n==============================================================\n\n");

	printf("  8   8          d8b   d8b\n");
	printf("  8www8  8   8   8'    8'   8d8b.d8b.  .d88  8d8b.  \n");
	printf("  8   8  8b d8  w8ww  w8ww  8P Y8P Y8  8  8  8P Y8  \n");
	printf("  8   8  `Y8P8   8     8    8   8   8  `Y88  8   8  \n\n");
	//Las letras las generé en esta página: "https://patorjk.com/software/taag/#p=display&f=Thick&t=Huffman"

                                            
    printf("  Carlos Alberto Tavera Arteaga - 1628839A\n");
	printf("  Algoritmo de Huffman\n\n");

	printf("==============================================================\n\n");


	char *letra;
	char x[MAX];
	char Cadena[MAX]; //= "ata la jaca a la estaca";
	char *eCadena,*dCadena;
	struct nodo *cabeza = NULL;
	struct codigo *codigo = NULL;



	printf("--------------------------------------------------\n");
	printf("Ingresar el mensaje a codificar:\n");
	fgets(Cadena,sizeof(Cadena),stdin);
	Cadena[strlen(Cadena)-1] = '\0';		// Borra el '\n' del final de la cadena
    printf("--------------------------------------------------\n");
	for(letra=Cadena;*letra;++letra)			
		cabeza = Frecuencia(cabeza,*letra);


	printf("Frecuencia de cada letra:");
	ImprimirLista(cabeza);
	printf("\n--------------------------------------------------\n");

	printf("Frecuencia de cada letra ordenada:");
	OrganizaFreq(&cabeza);
	ImprimirLista(cabeza);
	printf("\n--------------------------------------------------\n");

	printf("Longitud de la Lista ligada %d\n",Longitud(cabeza));
	printf("--------------------------------------------------\n");

	ConstruyeArbol(&cabeza); 				//Construye el Arbol de Huffman
	AsignaCodigo(cabeza,&codigo,x,0);     //Asigna los codigos

	printf("Letras codificadas:");
	ImprimirCod(codigo); 				    //Imprime los codigos

	printf("\n--------------------------------------------------\n");
	eCadena = Codifica(Cadena,codigo);		//Codifica el mensaje

	printf("Mensaje codificado:\n%s\n", eCadena);
	printf("--------------------------------------------------\n");

	printf("Mensaje empaquetado en bytes (Codigo BCD):\n");
	Empaquetar(eCadena);					//Empaquetar el mensaje
	printf("\n--------------------------------------------------\n");

	printf("Mensaje empaquetado en Hexadecimal:\n");
	EmpaquetarHex(eCadena);				//Empaquetar el mensaje en Hexadecimal
	printf("\n--------------------------------------------------\n");

	printf("\n==============================================================\n\n");	

}
//======================================================================






//======================================================================
//	Constructor Listas
//======================================================================
//  Funciones relacionadas con las Listas ligadas y ordenamiento.
//======================================================================

	//Cuenta la frecuencia de las letras:
struct nodo *Frecuencia(struct nodo *p, char letra)
{
	if(p == NULL){
		p = (struct nodo *)malloc(sizeof(struct nodo));
		p->letra = letra;
		p->contador = 1;
		p->siguiente = NULL;
		p->izquierda = NULL;
		p->derecha = NULL;
	}
	else if(p->letra == letra)
		p->contador += 1;
	else
		p->siguiente = Frecuencia(p->siguiente,letra);
	return p;
}

	//Imprime la lista sin organizar/organizada:
void ImprimirLista(struct nodo *cabeza)
{	
	while(cabeza != NULL){
		printf("\n%d : '%c'",cabeza->contador,cabeza->letra);
		cabeza = cabeza->siguiente;
	}	
}

	//Organiza las frecuencias de menor a mayor:
void OrganizaFreq(struct nodo **cabezaref)		
{
	struct nodo *actual,*OrganizaLista,*nodoSiguiente;

	OrganizaLista=NULL;
	actual=*cabezaref;

	while(actual!=NULL){
		nodoSiguiente = actual->siguiente;
		OrganizaInserta(&OrganizaLista,actual);
		actual=nodoSiguiente;
	}
	*cabezaref=OrganizaLista;
}


	//Inserta nodos de menor a mayor:
void OrganizaInserta(struct nodo **cabezaref,struct nodo *nodo_n)	
{
	struct nodo *actual,*nodoAnterior;

	actual=*cabezaref;
	nodoAnterior=NULL;

	while(actual!=NULL)
	{
		if( (actual->contador > nodo_n->contador) || ((actual->contador == nodo_n->contador) && (actual->letra > nodo_n->letra)) )
			break;
		nodoAnterior=actual;
		actual=actual->siguiente;
	}
	
	if(nodoAnterior == NULL)
	{											//Si está en la posicion "cabeza"
			nodo_n->siguiente=*cabezaref;
			*cabezaref=nodo_n;			
	}

	else
	{											//Si está en cualquier otra posición
			nodo_n->siguiente=actual;
			nodoAnterior->siguiente=nodo_n;

	}
}
//======================================================================






//======================================================================
//	Constructor Árbol
//======================================================================
//  Funciones relacionadas con el árbol de Huffman
//======================================================================
//
		
	//Construye el árbol de Huffman:
void ConstruyeArbol(struct nodo **cabezaref)
{	
	struct nodo *ultimos2,*Todo; //Todo = Todos los demas caracteres
	struct nodo *nodoNuevo;

	while(Longitud(*cabezaref) > 1){
		Separa(*cabezaref,&ultimos2,&Todo);
		nodoNuevo = CombinaNodo(ultimos2);
	    *cabezaref = Adjunta(Todo,nodoNuevo);
		OrganizaFreq(cabezaref);		
	}
}

	//Cuenta la longitud de la lista ligada
int Longitud(struct nodo *nodo)
{
	int longitud = 0;

	while(nodo != NULL){
		longitud++;
	    nodo = nodo->siguiente;
	}
	return longitud;
}

	//Separa los nodos
void Separa(struct nodo *cabeza,struct nodo **aref,struct nodo **bref)
{
	*aref = cabeza;
	*bref = (*aref)->siguiente->siguiente;
	
	(*aref)->siguiente->siguiente = NULL;
}

	//Combina los nodos
struct nodo *CombinaNodo(struct nodo *ultimos2)
{
	struct nodo *nodoNuevo = (struct nodo *)malloc(sizeof(struct nodo));

	nodoNuevo->contador = ultimos2->contador + ultimos2->siguiente->contador;
	nodoNuevo->siguiente = NULL;
	nodoNuevo->izquierda = ultimos2;
	nodoNuevo->derecha = ultimos2->siguiente;
	ultimos2->siguiente->siguiente = NULL;
	return nodoNuevo;
}
	
	//Adjunta los nodos
struct nodo *Adjunta(struct nodo *a,struct nodo *b)
{
	struct nodo *actual = a;

	if(actual == NULL)
		return b;

	while(actual->siguiente != NULL)
		actual = actual->siguiente;
		actual->siguiente = b;
		return a;
}

	//Esta funcion asigna 0 o 1:	
void AsignaCodigo(struct nodo *nodo,struct codigo **codigoref,char *x,int y)
{
	if( (nodo->izquierda == NULL) || (nodo->derecha == NULL) )
	{
		Mueve(codigoref ,Copia(x,y,'\0'),nodo->letra);
	}	
	else
	{		
		AsignaCodigo(nodo->izquierda,codigoref,Copia(x,y,'0'),y+1);
		AsignaCodigo(nodo->derecha,codigoref,Copia(x,y,'1'),y+1);	
	}
}

	//Mueve los nodos
void Mueve(struct codigo **codigoref,char *x,char letra)
{
	struct codigo *nodoNuevo = (struct codigo *)malloc(sizeof(struct codigo));

	nodoNuevo->x = strdup(x);
	nodoNuevo->letra = letra;
    nodoNuevo->siguiente = *codigoref;
	*codigoref = nodoNuevo;
}

	//Copia los nodos
char *Copia(char *s,int Indice,char letra)
{	
	*(s+Indice) = letra;
	return s;
}
	
	//Imprime el árbol
void ImprimirCod(struct codigo *nodo)
{
	while(nodo != NULL){
		printf("\n'%c' : %s",nodo->letra,nodo->x);
		nodo = nodo->siguiente;
	}
}
//======================================================================






//======================================================================
//	Función Codificar
//======================================================================

	// Codificar
char *Codifica(char *Cadena,struct codigo *codigo)
{
	char*m;
	char eCadena[MAX]={'\0'};

	for(m=Cadena;*m;++m)
		strcat(eCadena,returnCodigo(codigo,*m));
	return strdup(eCadena);
}

	// Regresa el codigo
char *returnCodigo(struct codigo *nodo,char m)
{
	while(nodo != NULL){
		if(nodo->letra == m)
			return nodo->x;
		nodo = nodo->siguiente;
	}
}

//======================================================================
//	Función Empaquetar
//======================================================================

	// Empaquetar
void Empaquetar(char *eCadena)
{
	int i,j = 0;
	int lim = 8;
	int cont = 0;
	
	if ( !eCadena[0] ) return;

	int longitud = strlen(eCadena);
	
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
		if ( i == longitud)
		{
			cont = 8;
			//Comprobar bytes
			if(longitud%8!=0)
			{
				for (int j = 0; j < 8-longitud%8; j++)
				{
					printf("0");
				}	
			}			
		}
		//Imprime caracter a caracter
		printf("%c", eCadena[i]);	
	}	    
}

	//Empaquetar Hexadecimal
void EmpaquetarHex(char *eCadena)
{
	//Es necesario copiar el codigo de "Empaquetar Bytes" para que no se modifique
	printf("\nCopiar el mensaje empaquetado en bytes para convertir en Hex:\n");
	scanf("%c", eCadena);
	scanf("%[^\n]", eCadena);
    char delimitador[] = " "; //Genera un token por cada espacio en el codigo
							  //Y lo convierte en hexadecimal
    char *token = strtok(eCadena, delimitador);
    
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