/* strtok example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
int num[2];
int i = 0;
  char str[] ="4;2";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str,";");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    num[i] = atoi(pch);
    pch = strtok (NULL, ";");
    i++;
  }

  printf("Numero 1: %d\n", num[0]);
  printf("Numero 2: %d\n", num[1]);
  return 0;
}


/*int main()
{
   char s1[49] = "Esto es un ejemplo para usar la funcion strtok()";
   char s2[4] = " \n\t";
   char *ptr;

   printf( "s1=%s\n", s1 );

   ptr = strtok( s1, s2 );    // Primera llamada => Primer token
   printf( "%s\n", ptr );
   while( (ptr = strtok( NULL, s2 )) != NULL )    // Posteriores llamadas
     printf( "%s\n", ptr );

   return 0;


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
}*/
