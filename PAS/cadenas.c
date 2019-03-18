#include <stdio.h>
#include <string.h>

int main(){

char numero1[30];
char numero2[30];

	printf("Introzuca un numero entero:");
	//fgets(numero1, 30);
	scanf("%s", numero1);
	printf("\n");

	printf("Introduzca un numero entero:");
	//fgets(numero2, 30);
	scanf("%s", numero2);
	printf("\n");

	char cadena[80];

	strcat(cadena, numero1);
	strcat(cadena, ";");
	strcat(cadena, numero2);

	printf("Cadena =%s\n",cadena);
}