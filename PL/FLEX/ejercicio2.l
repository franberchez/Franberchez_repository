/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Contamos el numero de palabras que hay en un fichero
      * Contamos el numero de veces que aparece una palabra en un fichero

   */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char cadena[50];
int contador;
%}


/* Definiciones regulares */
palabra		[a-zA-ZáéíóúÁÉÍÓÚñÑ]+


/***** Zona de las reglas *****/
%%

{palabra} {  
			if(strlen(cadena)>0){
				if(strcmp(yytext, cadena) == 0)
				{
					contador++;
				}
			}
			
			else contador ++; 
		  }

. ;

%%


/***** Zona de funciones auxiliares *****/

extern FILE *yyin, *yyout;

bool existeFichero(char* fichero)
{
	if(fopen(fichero, "r") == NULL) return false;

	return true;
}

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		printf("El numero de argumentos no es el correcto: ./ejercicio1 entrada.txt\n");
		return -1;
	}

	if (!existeFichero(argv[1]))
	{
		printf("EL fichero <%s> no existe\n", argv[1]);
		return -2;
	}

	if (argc == 3)
	{
		strcpy(cadena, argv[2]);
	}

	yyin=fopen(argv[1],"r");  

	yylex();

	fclose(yyin);

	switch(argc)
  	{
   		case 2: printf("%s contiene %d\n", argv[1], contador); 
        break;

   		case 3: printf("La palabra <%s> aparace %d veces en el fichero %s\n", cadena, contador, argv[1]); 
   		break;
  	}

	return 0;
}