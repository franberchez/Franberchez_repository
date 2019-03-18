#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

// Escribo los numeros en la tuberia1, y escribo los mensajes de gemelos, etc. en la tuberia2
// Extremo para leer -> leer(fildes[0]), extremo para escribir -> escribir(fildes[1]);

int main()
{

/* Estas son las variables para las tuberias y procesos */
int flag, status;
int tuberia1[2];
int tuberia2[2];
pid_t rf;

/* Parametros que necesito para la tuberia1 */
int numero1;
int numero2;
char cadena[30];
char resultado;
int num[2];
int i = 0;
char *pch;
int cont = 0;
int cont1 = 0;

// Creamos la tuberia1
status = pipe(tuberia1);
if(status == -1)
{
	printf("Error al crear la tuberia1\n");
	exit(-1);
}

// Creamos la tuberia2
status = pipe(tuberia2);
if(status == -1)
{
	printf("Error al crear la tuberia2\n");
	exit(-1);
}

rf = fork();

switch(rf)
{
	case -1:
		printf("No se ha podido crear el proceso hijo...\n");
		exit(EXIT_FAILURE);

	case 0:
		printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

		// Cierro el extremo de escritura de la tuberia 1
		if(close(tuberia1[1])==-1)
		{
			printf("\n[HIJO]: Error al cerrar el extremo de lectura de la tuberia1");
			exit(EXIT_FAILURE);
		}

		// Recibimos los enteros a traves de la tuberia1
		resultado = read(tuberia1[0], cadena, 30);
		if(resultado != 30)
		{
			printf("\n[HIJO]: Error al leer de la tuberia1");
			exit(EXIT_FAILURE);
		}
		printf("\n[HIJO]: Leido %s de la tuberia1\n", cadena);

		// Cerramos el extremo que hemos usado
		if (close(tuberia1[0])==-1)
		{
			printf("\n[HIJO]: Error al cerrar el extremo de lectura de la tuberia1");
			exit(EXIT_FAILURE);
		}

		pch = strtok(&resultado, ";"); // SI LE PONGO EL & SE QUITA EL WARNING PERO ESTO VA A DAR ERROR PORQUE STRTOK NECESITA CHAR*

		while( pch != NULL )
		{
			num[i] = atoi(pch);
			pch = strtok(NULL, ";");
			i++;
		}

		// Cerramos el extremo de lectura de la tuberia2
		if (close(tuberia2[0])==-1)
		{
			printf("\n[HIJO]: Error al cerrar el extremo de lectura de la tuberia2");
			exit(EXIT_FAILURE);
		}

		for(i = 1; i<num[0]; i++){
			if(num[0]%i==0){
				cont++;
			}
		}

		for(i = 1; i<num[1]; i++){
			if(num[1]%i==0){
				cont1++;
			}
		}

		if( (cont==2)||(cont1==2) )
		{
			if( (cont==2)&&(cont1==2) )
			{
				if( (num[0]==num[1]+2)||(num[1]==num[0]+2)  )
				{
					strcpy(cadena,"gemelos");
					resultado = write(tuberia2[1], cadena, 30);

						if(resultado != 30)
						{
							printf("\n[HIJO]: Error al escribir en la tuberia2, en caso de ser gemelos");
							exit(EXIT_FAILURE);
						}
				}

				else
				{
					strcpy(cadena,"primos");
					resultado = write(tuberia2[1], cadena, 30);

						if(resultado != 30)
						{
							printf("\n[HIJO]: Error al escribir en la tuberia2, en caso de ser primos");
							exit(EXIT_FAILURE);
						}
				}
				
			}

			else
			{
				strcpy(cadena,"primos");
				resultado = write(tuberia2[1], cadena, 30);

					if(resultado != 30)
					{
						printf("\n[HIJO]: Error al escribir en la tuberia2, en caso de ser primos");
						exit(EXIT_FAILURE);
					}
			}
		}

		else
		{
			strcpy(cadena,"no primos");
			resultado = write(tuberia2[1], cadena, 30);

				if(resultado != 30)
				{
					printf("\n[HIJO]: Error al escribir en la tuberia2, en caso de ser no primos");
					exit(EXIT_FAILURE);
				}
		}

		// Ahora cerramos el extremo que hemos usado
		if(close(tuberia2[1])==-1)
		{
			printf("\n[HIJO]: Error al cerrar el extremo de escritura de la tuberia2");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
		

	default:
		if(close(tuberia1[0])==-1){
			printf("\n[PADRE]: Error al cerrar el extremo de lectura en la tuberia1 del padre AAAAAAAAAA");
			exit(EXIT_FAILURE);
		}

		printf("\n[PADRE]: Mi PID es %d y el pid de mi hijo es %d\n", getpid(), rf);
		close(tuberia1[0]);

		sleep(1);
		printf("\n[PADRE]: Inserte el valor del primer numero: ");
		scanf("%d", &numero1);

		printf("\n[PADRE]: Inserte el valor del segundo numero: ");
		scanf("%d", &numero2);

		// Generamos la cadena que le vamos a pasar a la tuberia1
		sprintf(cadena, "%d;%d", numero1, numero2);

		// Como no necesita leer cierra el extremo de lectura

		// Enviamos los mensajes a traves de la tuberia1
		resultado = write(tuberia1[1], cadena, 30);
		if(resultado != 30)
		{
			printf("\n[PADRE]: Error al escribir en la tuberia1");
			exit(EXIT_FAILURE);
		}

		// Ahora cerramos el extremo que hemos usado
		if (close(tuberia1[1])==-1)
		{
			printf("\n[PADRE]: Error al cerrar el extremo del escritura de la tuberia1");
			exit(EXIT_FAILURE);
		}
		printf("\n[PADRE]: tuberia1 cerrada");

		/* Espera a los hijos */
		while ( (flag=wait(&status)) > 0 ) 
		{
			if (WIFEXITED(status)) {
				printf("\n[PADRE]: Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			} 
			else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
				printf("\n[PADRE]:, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			} 

			}
			if (flag==(pid_t)-1 && errno==ECHILD)
			{
				printf("\n[PADRE]: Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
			}
			else
			{
				printf("\n[PADRE]: Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
				exit(EXIT_FAILURE);
			}	

}

exit(EXIT_SUCCESS);

}