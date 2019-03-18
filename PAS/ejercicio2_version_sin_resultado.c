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
const int BSIZE = 100;

char envio[BSIZE];
char respuesta[BSIZE];
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

			/////////////////////////////////////////
			////// EL HIJO LEE DE LA TUBERIA 1 //////
			/////////////////////////////////////////

			// Cierro el extremo de escritura de la tuberia 1
			if(close(tuberia1[1])==-1)
			{
				printf("[HIJO]: Error al cerrar el extremo de lectura de la tuberia1\n");
				exit(EXIT_FAILURE);
			}

			// Recibimos los enteros a traves de la tuberia1
			if(read(tuberia1[0], respuesta, BSIZE) == -1)
			{
				printf("[HIJO]: Error al leer de la tuberia1\n");
				exit(EXIT_FAILURE);
			}
			printf("[HIJO]: Leido %s de la tuberia1\n", respuesta);

			// Cerramos el extremo que hemos usado
			if (close(tuberia1[0])==-1)
			{
				printf("[HIJO]: Error al cerrar el extremo de lectura de la tuberia1\n");
				exit(EXIT_FAILURE);
			}

			else printf("[HIJO]: Tuberia 1 cerrada...\n");

			/////////////////////////////////////////////
			////// EL HIJO ESCRIBE EN LA TUBERIA 2 //////
			/////////////////////////////////////////////

			// Cerramos el extremo de lectura de la tuberia2
			if (close(tuberia2[0])==-1)
			{
				printf("[HIJO]: Error al cerrar el extremo de lectura de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			pch = strtok(respuesta, ";");

			while( pch != NULL )
			{
				num[i] = atoi(pch);
				pch = strtok(NULL, ";");
				i++;
			}


			for(i = 1; i<=num[0]; i++){
				if(num[0]%i==0){
					cont++;
				}
			}

			for(i = 1; i<=num[1]; i++){
				if(num[1]%i==0){
					cont1++;
				}
			}

			if( (cont==2)&&(cont1==2) )
			{
				if( (num[0]==num[1]+2)||(num[1]==num[0]+2)  )
				{
					strcpy(respuesta,"gemelos");
					printf("[HIJO]: Envio el mensaje %s a mi padre\n",respuesta);

						if(write(tuberia2[1], respuesta, BSIZE) == -1)
						{
							printf("[HIJO]: Error al escribir en la tuberia2, en caso de ser gemelos\n");
							exit(EXIT_FAILURE);
						}
				}

				else
				{
					strcpy(respuesta,"primos");
					printf("[HIJO]: Envio el mensaje %s a mi padre\n",respuesta);

						if(write(tuberia2[1], respuesta, BSIZE) == -1)
						{
							printf("[HIJO]: Error al escribir en la tuberia2, en caso de ser primos\n");
							exit(EXIT_FAILURE);
						}
				}
					
			}

			else
			{
				strcpy(respuesta,"no-primos");
				printf("[HIJO]: Envio el mensaje %s a mi padre\n",respuesta);

					if(write(tuberia2[1], respuesta, BSIZE) == -1)
					{
						printf("[HIJO]: Error al escribir en la tuberia2, en caso de ser no primos\n");
						exit(EXIT_FAILURE);
					}
			}

			// Ahora cerramos el extremo que hemos usado
			if(close(tuberia2[1])==-1)
			{
				printf("[HIJO]: Error al cerrar el extremo de escritura de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			else printf("[HIJO]: Tuberia 2 cerrada...\n");

			exit(EXIT_SUCCESS);
			

		default:

			//////////////////////////////////////////////
			////// EL PADRE ESCRIBE EN LA TUBERIA 1 //////
			//////////////////////////////////////////////

			// Como no necesita leer cierra el extremo de lectura
			if(close(tuberia1[0])==-1){
				printf("[PADRE]: Error al cerrar el extremo de lectura en la tuberia1 del padre\n");
				exit(EXIT_FAILURE);
			}

			printf("[PADRE]: Mi PID es %d y el pid de mi hijo es %d\n", getpid(), rf);

			printf("[PADRE]: Inserte el valor del primer numero: ");
			fflush(stdout);
			scanf("%d", &numero1);

			printf("[PADRE]: Inserte el valor del segundo numero: ");
			fflush(stdout);
			scanf("%d", &numero2);

			// Generamos la cadena que le vamos a pasar a la tuberia1
			sprintf(envio, "%d;%d", numero1, numero2);


			// Enviamos los mensajes a traves de la tuberia1
			if(write(tuberia1[1], envio, BSIZE) == -1)
			{
				printf("[PADRE]: Error al escribir en la tuberia1\n");
				exit(EXIT_FAILURE);
			}

			else printf("[PADRE]: He escrito %s en la tuberia1\n", envio);

			// Ahora cerramos el extremo que hemos usado
			if (close(tuberia1[1])==-1)
			{
				printf("[PADRE]: Error al cerrar el extremo del escritura de la tuberia1\n");
				exit(EXIT_FAILURE);
			}
			else printf("[PADRE]: tuberia1 cerrada...\n");

			//////////////////////////////////////////
			////// EL PADRE LEE DE LA TUBERIA 2 //////
			//////////////////////////////////////////

			// Cerramos el extremo de escritura de la tuberia2
			if(close(tuberia2[1])==-1)
			{
				printf("[PADRE]: Error al cerrar el extremo de escritura de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			if(read(tuberia2[0], respuesta, BSIZE) == -1)
			{
				printf("[PADRE]: Error al leer de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			else printf("[PADRE]: He leido %s de la tuberia2\n", respuesta);

			// Ahora cerramos el extremo que hemos usado
			if(close(tuberia2[0]) == -1)
			{
				printf("[PADRE]: Error al cerrar el extremo de lectura de la tuberia2\n");
				exit(EXIT_FAILURE);
			}

			else printf("[PADRE]: Tuberia 2 cerrada...\n");

			/* Espera a los hijos */
			while ( (flag=wait(&status)) > 0 ) 
			{
				if (WIFEXITED(status)) 
				{
					printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
					printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
				} else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
					printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
				} else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
					printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);		  
				}	
			}
			if (flag==(pid_t)-1 && errno==ECHILD)
			{
				printf("Proceso Padre, valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
			}
			else
			{
				printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
				exit(EXIT_FAILURE);
			}	
				
			exit(EXIT_SUCCESS);

	}//switch

	exit(EXIT_SUCCESS);

}