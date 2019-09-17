#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

 
int main ( )
{

	/*---------------------------------------------------------
		TENGO QUE MODIFICAR WEL CLIENTE PARA QUE MANDE:
			- DAY
			- TIME
			- DAYTIME
	----------------------------------------------------------*/  
		int contador = 0;
		int opcion;

		printf("\nElija una opcion:\n");
		printf("\t1. DAY\n");
		printf("\t2. TIME\n");
		printf("\t3. DAYTIME\n\n");

		printf("Escriba su opcion: ");
		scanf("%d", &opcion);

		char cadena [80];

		if(opcion == 1)
		{
			strcpy(cadena, "DAY");
		}
		else
		{
			if(opcion == 2)
			{
				strcpy(cadena, "TIME");
			}

			else strcpy(cadena, "DAYTIME");
		}



	/*---------------------------------------------------- 
		Descriptor del socket y buffer para datos
	-----------------------------------------------------*/
		int Socket_Cliente;
		int Datos;

   
   	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
	   	struct sockaddr_in Servidor;  
	   	socklen_t Longitud_Servidor;
	  
  
   	/* --------------------------------------------------
			Se abre el socket cliente
	---------------------------------------------------*/
		Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
		if (Socket_Cliente == -1)
		{
			printf ("No se puede abrir el socket cliente\n");
    			exit (-1);	
		}

 	/*---------------------------------------------------------------------
		Necesitamos una estructura con la informaci\ufffdn del Servidor
		para poder solicitarle un servicio.
   	----------------------------------------------------------------------*/
		Servidor.sin_family = AF_INET;
		Servidor.sin_port = htons(2000);
		Servidor.sin_addr.s_addr =  inet_addr("127.0.0.1"); // direccion de autobucle que nos sirve para simular una comunicacion dentro del mismo equipo
  	 	Longitud_Servidor = sizeof(Servidor);
	

	/*------------------------------------------------------------------------
		Se genera un n\ufffdmero aleatorio, que es el que se le manda al
		servidor.
	------------------------------------------------------------------------ */
   		printf ("Envio: %s\n", cadena);

   	
	/*-----------------------------------------------------------------------
		Se env\ufffda mensaje al Servidor
	-----------------------------------------------------------------------*/
		int enviado = sendto (Socket_Cliente, cadena, sizeof(cadena), 0, // como Datos se ha definido como entero lo que hacemos es un casting para que quede como char*
			(struct sockaddr *) &Servidor, Longitud_Servidor);
   
	   	if (enviado < 0)
	    	{
				printf("Error al solicitar el servicio\n");
			}
	    	else
			{
   
	/*----------------------------------------------------------------------
		Esperamos la respuesta del Servidor
	----------------------------------------------------------------------- */ 


		int recibido = recvfrom (Socket_Cliente, cadena, sizeof(cadena), 0, // si el servidor no esta activo nos vamos a quedar bloqueado
		(struct sockaddr *) &Servidor, &Longitud_Servidor);
			
   		if (recibido > 0)
      		printf ("Leido: %s\n", cadena);
   		else
      		printf ("Error al leer del servidor\n");
		
		}
		
		close(Socket_Cliente);

	return 0;
}
