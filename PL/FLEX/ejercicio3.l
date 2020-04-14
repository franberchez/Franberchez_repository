/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Se transforman los numeros enteros en reales

   */

#include <stdio.h>
#include <stdbool.h>
#include "ejercicio3.h"
%}
espacio				[ \t\n]
espacios			{espacio}+
letra				[a-zA-Z]
digito				[0-9]
guion				[_]
identificador		{letra}({letra}|{digito}|{guion}({letra}|{digito}))*
numero				{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
numero_fallo		{digito}+(,{digito}+)?(E[+\-]?{digito}+)?
cadena				"'"([^'\\]|"\\\'")*"'"

/***** Zona de las reglas *****/
%%
{espacios}   { /* no se hace nada */ ; }

(?i:inicio)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, inicio);}

(?i:fin)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, fin);}

(?i:leer)	    	{printf("\n Palabra reservada: %s --> token %d\n", yytext, leer);}

(?i:escribir)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, escribir);}

(?i:si)				{printf("\n Palabra reservada: %s --> token %d\n", yytext, si);}

(?i:entonces)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, entonces);}

(?i:si_no)	 		{printf("\n Palabra reservada: %s --> token %d\n", yytext, si_no);}

(?i:fin_si) 		{printf("\n Palabra reservada: %s --> token %d\n", yytext, fin_si);}

(?i:mientras)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, mientras);}

(?i:hacer)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, hacer);}

(?i:fin_mientras)	{printf("\n Palabra reservada: %s --> token %d\n", yytext, fin_mientras);}

(?i:repetir)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, repetir);}

(?i:hasta_que)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, hasta_que);}

(?i:para)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, para);}

(?i:desde)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, desde);}

(?i:hasta)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, hasta);}

(?i:paso)			{printf("\n Palabra reservada: %s --> token %d\n", yytext, paso);}

(?i:fin_para)		{printf("\n Palabra reservada: %s --> token %d\n", yytext, fin_para);}

{identificador}		{printf("\n Identificador: %s --> token %d\n", yytext, ID);}

{numero}			{printf("\n Numero: %s --> token %d\n", yytext, NUMERO);}

{cadena}			{printf("\n Cadena: %s --> token %d\n", yytext, CADENA);}

":="				{printf("\n Operador asignacion: %s --> token %d\n", yytext, ASIGNACION);}

"+"					{printf("\n Operador suma: %s --> token %d\n", yytext, SUMA);}

"-"					{printf("\n Operador resta: %s --> token %d\n", yytext, RESTA);}

"*"					{printf("\n Operador producto: %s --> token %d\n", yytext, PRODUCTO);}

"/"					{printf("\n Operador division: %s --> token %d\n", yytext, DIVISION);}

"_mod"				{printf("\n Operador modulo: %s --> token %d\n", yytext, MODULO);}

"**"				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

"||"				{printf("\n Operador concatenacion: %s --> token %d\n", yytext, CONCATENACION);}

"<"				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

"<="				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

">"				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

">="				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

"=="				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

"<>"				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

".o."				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

".y."				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

".no."				{printf("\n Operador potencia: %s --> token %d\n", yytext, POTENCIA);}

[a-zA-Z0-9\_]+		{printf("\n Identificador no reconocido: %s --> token %d\n", yytext, ID_FALLO);}

{numero_fallo}		{printf("\n Numero no reconocido: %s --> token %d\n", yytext, NUMERO_FALLO);}

[_\.|\||?|=|!|¡|?|¿|%|@|€]+			{printf("\n Operador no reconocido: %s --> token %d\n", yytext, OPERADOR_FALLO);}

.           		;
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
		printf("El numero de argumentos no es el correcto: ./ejercicio3 entrada.txt\n");
		return -1;
	}

	if (!existeFichero(argv[1]))
	{
		printf("EL fichero <%s> no existe\n", argv[1]);
		return -2;
	}

	yyin=fopen(argv[1],"r");  

	yylex();

	fclose(yyin);

	return 0;
}