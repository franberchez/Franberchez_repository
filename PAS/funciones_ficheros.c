/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
}

/*

fgets es la alternativa segura a gets, ya que esta permite establcer el maximo numero de caracteres que pueden leerse.
Primero se establece donde se quiere copiar la linea leida. A continuacion el maximo numero de caracteres.

fgets, lo que recibe es lo siguiente char* fgets(char* s, int n, FILE* f)

siendo la cadena primera que le paso una cadena de tamaño n, es decir, creo la siguiente variable:
char cadena[1024];
Lo que hago es crear por ejemplo una cadena de 1024 elementos y esta es la que le paso a fgets, por ejemplo:

fgets(cadena, 1024, f);

*/