#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <regex.h>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MSG_STOP "exit"
#define QUEUE_NAME "/una_cola"
#define MAX_SIZE 1024

void imprimir_uso() //nos muestra por pantalla para que sirve cada comando
{
    printf("Uso del programa: ejercicio4-servidor [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help\t	Imprimir esta ayuda\n");
    printf("-r, --regex=EXPR\t	Expresión regular a utilizar\n");
}

// Descriptor de la cola
mqd_t mq = -1;

// Nombre para las colas
char cola[100];

int main(int argc, char **argv)
{
	/* Variables para el getopt */
	int eflag = 0;
	char *regexValue = NULL;
	int c;
	int option_index;
	static struct option long_options[] =
	{
		{"regex",  required_argument,	   0, 'r'},
		{"help",     no_argument,	   0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

	// flag que indica cuando hay que parar
	int must_stop = 0;

	// Número de bytes leidos
	ssize_t bytes_read;

	/* Variables para la regex */
	regex_t regex;
	int reti;
	char msgbuf[100];

	// Atributos de la cola
	struct mq_attr attr;

	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];

	// Para realizar el fork
	pid_t rf, flag;
	int status;

	while ((c = getopt_long (argc, argv, "hr:",long_options, &option_index))!=-1)
	{
		
		switch (c)
		{
			case 'h':
				imprimir_uso();				
				break;
			case 'r':
				regexValue = optarg;
				break;
			case '?':
				if (optopt == 'r')
					fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
				else
					fprintf (stderr, "Carácter de opción desconocido `\\x%x'.\n", optopt);
					imprimir_uso();
			default:			
				exit(EXIT_SUCCESS);
		}

	}

	if(regexValue==NULL)
	{
	   imprimir_uso();
	   exit(EXIT_SUCCESS);
	}

	printf("[PADRE]: Valor de regexvalue en servidor:%s\n",regexValue);

	/* Compilar la expresión regular */
	reti = regcomp(&regex, regexValue, 0);	// regexValue lo que va contener va a ser el hola		
	if( reti )
	{
		fprintf(stderr, "No pude compilar la expresión regular\n");
		exit(EXIT_FAILURE);
	}

	/* 

		Apertura de la cola
		O_CREAT: si no existe, se crea
		O_RDWR: lectura/escritura
		O_RDONLY: solo lectura
		O_WRONLY: solo escritura
		0644: permisos rw-r--r--  
		permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
		attr: estructura con atributos para la cola  

	*/

	// Nombre para las colas
	sprintf(cola, "%s-%s", QUEUE_NAME, getenv("USER"));

	// Realizar el fork
	rf = fork();

	switch (rf)
	{
		case -1: // Error al crear el hijo
			printf("Error al crear el proceso hijo\n");
			exit(EXIT_FAILURE);

		case 0: // Proceso HIJO
			mq = mq_open(cola, O_CREAT | O_RDWR, 0644, &attr);
			if( mq == -1)
			{
		     	perror("[HIJO]: Error al abrir la cola del servidor");
		   		exit(EXIT_FAILURE);
			}

			printf("[HIJO]: Mandando mensajes al padre (escribir \"%s\" para parar):\n", MSG_STOP);

			do
			{
				printf("[HIJO]: > ");

				fflush(stdout);                  // Limpia buffer de salida
				memset(buffer, 0, MAX_SIZE);     // Pone a 0 el buffer

				fgets(buffer, MAX_SIZE, stdin);  //para leer por la entrada estandar del sistema

				// Enviar y comprobar si el mensaje se manda
				if(mq_send(mq, buffer, MAX_SIZE, 0) != 0)//voya enviar por la cola servidora lo que acabo de leer
				{
					perror("[HIJO]: Error al enviar el mensaje");
					exit(EXIT_FAILURE);
				}

				//printf("[HIJO]: Envio el mensaje %s\n", buffer);

				//sprintf(msgbuf,"[HIJO]: Enviado el mensaje: %s", buffer); //metemos lo que vamos a enviar y lo comparo con exit
				if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				{
					must_stop=1;
				}

				else
				{
					// Recibir el mensaje
					bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); //tengo que esperar hasta que haya algo en la cola

					// Comprar que la recepción es correcto (bytes leidos no son negativos)
					if(bytes_read < 0)
					{
						perror("[HIJO]: Error al recibir el mensaje");
						exit(EXIT_FAILURE);
					}
					  
					printf("[HIJO]: Recibido el mensaje: %s\n", buffer); //me imprime el mensaje de empareja o no empareja
					sprintf(msgbuf,"[HIJO]: Recibido el mensaje: %s", buffer); // NO SABEMOS SI ESTA LINEA VALE PARA ALGO
					if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
					{
						must_stop=1;
					}
				}

			}while(!must_stop);

			break; //Saldría del switch()

		default: // Proceso PADRE

			//Apertatura de la cola
			mq = mq_open(cola, O_CREAT | O_RDWR, 0644, &attr);
			if(mq==-1)
			{
				perror("[PADRE]: Error en la apertura de la cola");
				exit(-1);
			}

			//printf ("[PADRE]: mi PID es %d y el PID de mi hijo es %d \n", getpid(), rf);
			//printf ("[PADRE]: recibiendo mensaje (espera bloqueante)...\n");

			do
			{

				// Recibir el mensaje
				bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); //llamada bloqueante, me pongo a esperar hasta recibir un mensaje que en nuestro caso es hola
				// Comprar que la recepción es correcto (bytes leidos no son negativos)
				if(bytes_read < 0)
				{
					perror("[PADRE]: Error al recibir el mensaje");
					exit(EXIT_FAILURE);
				}

				// Comprobar el fin del bucle
				if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				{
					must_stop = 1;
				}

				else
				{

					printf("[PADRE]: Recibido el mensaje: %s\n", buffer);
					sprintf(msgbuf,"[PADRE]: Recibido el mensaje: %s", buffer);

					/* Comprobar la expresión regular sobre la cadena pasada como argumento */
					reti = regexec(&regex, buffer, 0, NULL, 0); //compruebo si dentro del buffer esta almacenado el hola
					
				    fflush(stdout);                  // Limpiar buffer de salida
				    memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer		  
				  
					if(reti == 0)
					{
						strcpy(buffer,"Empareja");
					}
					else if( reti == REG_NOMATCH )
					{
						strcpy(buffer,"No Empareja");
					}
					else
					{
						regerror(reti, &regex, msgbuf, sizeof(msgbuf));
						fprintf(stderr, "Falló el matching de la expresión regular: %s\n", msgbuf);
						strcpy(buffer,MSG_STOP);
					}
					
					// Enviar y comprobar si el mensaje se manda
					if(mq_send(mq, buffer, MAX_SIZE, 0) != 0) //envio empareja o no empareja hasta que yo reciba la palabra exit
					{
						perror("[PADRE]: Error al enviar el mensaje");
						exit(-1);
					}

					sprintf(msgbuf,"[PADRE]: Enviado el mensaje: %s", buffer);

				}

			}while(!must_stop);

			/* Liberar la expresión regular utilizada */
			regfree(&regex);

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


	}// fin switch

			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[PADRE]: Error cerrando la cola");
				exit(-1);
			}
			printf("[PADRE]: Cola cerrada.\n");

			// Eliminar la cola
			if(mq_unlink(cola) == -1)
			{
				perror("[PADRE]: Error eliminando la cola");
				exit(-1);
			}

	exit(EXIT_SUCCESS);

}