#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "common.h"

// Apuntador al fichero de log (se utilizará en el ejercicio resumen)
FILE *fLog = NULL;

// Cola del servidor
mqd_t mq_server = -1;

// Cola del cliente
mqd_t mq_client = -1;

// Nombre para las colas
char clientQueue[100];
char serverQueue[100];

//Estructura de la cola
struct mq_attr attr;


//Prototipo de funcion
void funcionLog(char *);

// Función que procesará EL FINAL
void finPrograma(int value);

void mi_manejador_sigint(int signal)
{
    printf("Capturé la señal SIGINT y no salgo!\n");
    finPrograma(-1);
}


/* Nuestro manejador para SIGTERM */
void mi_manejador_sigterm(int signal)
{
    int i;
    printf("Capturé la señal SIGTERM y voy a salir de manera ordenada\n");
    for(i=0; i<3; i++)
    {
        printf("Hasta luego... cerrando ficheros...\n");
        sleep(1);
    }
    finPrograma(-1);
}

int main(int argc, char **argv)
{

	if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
    printf("No puedo asociar la señal SIGINT al manejador!\n");

    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];

	// Buffer para mensajes
	char msgbuf[100];
	
	//Inicializanos las variables de la cola
	attr.mq_maxmsg = 10; // Maximo numero de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	// Nombre para las colas
	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));

	// Abrir la cola del servidor
	mq_server = mq_open(serverQueue, O_CREAT | O_WRONLY, 0644, &attr);
	if( mq_server == (mqd_t)-1)
	{
    	perror("Error al abrir la cola del servidor");
    	funcionLog("Error al abrir la cola del servidor");
    	exit(EXIT_FAILURE);
	}

	// Abrir la cola del cliente
	mq_client = mq_open(clientQueue, O_CREAT | O_RDONLY, 0644, &attr); //abro la cola que voy a utilizar para leer
	if( mq_client == (mqd_t)-1)
	{
    	perror("Error al abrir la cola del cliente");
    	funcionLog("Error al abrir la cola del cliente");
   		exit(EXIT_FAILURE);
	}

	// flag que indica cuando hay que parar
	int must_stop = 0;
	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);

	do 
	{
		printf("> ");

		fflush(stdout);                  // Limpiar buffer de salida como en MP
		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer


		fgets(buffer, MAX_SIZE, stdin);  //para leer por la entrada estandar del sistema

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)//voya enviar por la cola servidora lo que acabo de leer
		{
			perror("Error al enviar el mensaje");
			funcionLog("Error al enviar el mensaje");
			exit(EXIT_FAILURE);
		}

		funcionLog(buffer);
	
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer); //metemos lo que vamos a enviar y lo comparo con exit
		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop=1;
		else
		{
			// Número de bytes leidos
			ssize_t bytes_read;
			// Recibir el mensaje
			bytes_read = mq_receive(mq_client, buffer, MAX_SIZE, NULL); //tengo que esperar hasta que haya algo en la cola
			// Comprar que la recepción es correcto (bytes leidos no son negativos)
			if(bytes_read < 0)
			{
				perror("Error al recibir el mensaje");
				funcionLog("Error al recibir el mensaje");
				exit(EXIT_FAILURE);
			}

			funcionLog(buffer);
			  
			printf("Recibido el mensaje: %s\n", buffer); //me imprime el mensaje de empareja o no empareja
			sprintf(msgbuf,"Recibido el mensaje: %s", buffer); // NO SABEMOS SI ESTA LINEA VALE PARA ALGO
			if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				must_stop=1;
		}
		// Iterar hasta escribir el código de salida
	}while (!must_stop);

	/*if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");

    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");*/


	finPrograma(-1);
	mq_client = mq_server = -1;
	return 0;
}

void finPrograma(int value) //esta funcion lo unico que hace es cerrar colas
{
   char msgbuf[100];

	if(mq_client!=-1)
	{
		// Cerrar la cola del servidor
		if(mq_close(mq_client) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del cliente");
			exit(EXIT_FAILURE);
		}
	}
	
	if(mq_server!=-1)//termina el pronceso de envio y recepcion de finalizacion de las colas
	{
		// Buffer para intercambiar mensajes
		char buffer[MAX_SIZE];
		strcpy(buffer,MSG_STOP);
		
		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			exit(EXIT_FAILURE);
		}
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer);

		// Cerrar la cola del servidor
		if(mq_close(mq_server) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del servidor");
			exit(EXIT_FAILURE);
		}
	}
	mq_client = mq_server = -1;	
	exit(0);
}


// Función auxiliar, escritura de un log
void funcionLog(char *mensaje) 
{
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero,"log-cliente.txt");
	if(fLog==NULL)
	{
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL)
		{
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);
	
	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir,fLog);
	if ( resultado < 0)
		perror("Error escribiendo en el fichero de log");

	fclose(fLog);
	fLog=NULL;
}