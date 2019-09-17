#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include <string.h>


/*
 * El servidor ofrece el servicio de incrementar un n\ufffdmero recibido de un cliente
 */
 
int main ()
{

	/*---------------------------------------------------- 
		Declaro las variables para enviar un mensaje al
		cliente relacionado con DAY, TIME o DAYTIME             
	-----------------------------------------------------*/
	time_t tiempo;
	struct tm * stTm;
	char cadena_enviada [80];
	char cadena_recibida [80];

	tiempo = time(NULL);

	setlocale(LC_ALL,"");

	stTm = localtime(&tiempo);

	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int Socket_Servidor;
	struct sockaddr_in Servidor;
	

	/* -----------------------------------------------------
   		Informaci\ufffdn del Cliente
   	-----------------------------------------------------*/
   	struct sockaddr_in Cliente;
	socklen_t Longitud_Cliente;
	
	
	/* --------------------------------------------------
		Se abre el socket Servidor
	---------------------------------------------------*/
	Socket_Servidor = socket (AF_INET, SOCK_DGRAM, 0);
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);	
	}

	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura servidor, necesaria
		para la llamada a la funcion bind().
	-------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr = htonl(INADDR_ANY); 

	if (bind (Socket_Servidor, (struct sockaddr *)&Servidor, sizeof (Servidor)) == -1) // nos sirve para hacer la asociacion
	// puede dar error cunado no funciona o el cliente o el servidor, por lo que debo usar (ctrl + c) para matar el proceso
	{
		close (Socket_Servidor);
		exit (-1);
	}
	

  	/*---------------------------------------------------------------------
		Del cliente s\ufffdlo necesitamos el tama\ufffdo de su estructura, el 
		resto de informaci\ufffdn (familia, puerto, ip), la obtendremos 
		nos la proporcionar\ufffd el propio m\ufffdtodo recvfrom, cuando
		recibamos la llamada de un cliente.
   ----------------------------------------------------------------------*/
	Longitud_Cliente = sizeof (Cliente);

   	
	/*-----------------------------------------------------------------------
		El servidor espera continuamente los mensajes de los clientes
	------------------------------------------------------------------------ */
	while (1) // hacemos un bucle infinito
	{
    /* -----------------------------------------------------------------
			Esperamos la llamada de alg\ufffdn cliente que le pida algo
		-------------------------------------------------------------------*/
      	int recibido = recvfrom (Socket_Servidor, cadena_recibida, sizeof(cadena_recibida), 0,
			(struct sockaddr *) &Cliente, &Longitud_Cliente);



		/* -----------------------------------------------------------------
			Comprobamos si hemos recibido alguna informaci\ufffdn 
		-------------------------------------------------------------------*/
		if (recibido > 0)
		{

			if (strcmp(cadena_recibida, "DAY") == 0 )
			{
				strftime(cadena_enviada, 80, "%A, %d de %B de %Y", stTm);
			}

			else
			{
				if (strcmp(cadena_recibida, "TIME") == 0 )
				{
					strftime(cadena_enviada, 80, "%H:%M:%S", stTm);
				}

				else strftime(cadena_enviada, 80, "%A, %d de %B de %Y; %H:%M:%S", stTm);
			}

				/*-----------------------------------------------------------------
				Incrementamos el valor que nos ha enviado el cliente 
				------------------------------------------------------------------*/
      		printf ("Recibido: %s, envio: %s\n", cadena_recibida, cadena_enviada);
      
      			/* ------------------------------------------------------------------
				Devolvemos el n\ufffdmero incrementado al cliente
				--------------------------------------------------------------------*/
			int enviado = sendto (Socket_Servidor, cadena_enviada, sizeof(cadena_enviada), 0,
			(struct sockaddr *) &Cliente, Longitud_Cliente);

		}

    }
	 
	 close(Socket_Servidor);

	return 0;
}
