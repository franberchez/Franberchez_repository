/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Se transforman los numeros enteros en reales

   */

#include <stdio.h>
#include <stdbool.h>
%}


/* Definiciones regulares */
digito		[0-9]
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?


/***** Zona de las reglas *****/
%%

{numero} {  fprintf( yyout, "%.1f", atof(yytext) ); }
. {ECHO;}

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

	if (argc != 3)
	{
		printf("El numero de argumentos no es el correcto: ./ejercicio1 entrada.txt salida.txt\n");
		return -1;
	}

	if (!existeFichero(argv[1]))
	{
		printf("EL fichero <%s> no existe\n", argv[1]);
		return -2;
	}

	if (existeFichero(argv[2]))
	{
		printf("Ya esxiste el fichero de salida <%s>, debe introducir otro nuevo\n", argv[2]);
		return -3;
	}

	yyin=fopen(argv[1],"r");  
	yyout=fopen(argv[2],"w");

	yylex();

	fclose(yyin);
	fclose(yyout);

	return 0;
}