/*

1. Implementar un proceso padre que cree 3 hijos y luego espera a que finalicen antes de
	finalizar él mismo.

2. Los tres hijos comparten un vector de 100 enteros. Cada uno de ellos ha de realizar una de
	las siguientes tareas:

	◦ Pedir un índice del vector y un valor entero por teclado y almacenar en la posición
		correspondiente el valor leído. Esta operación se ha de repetir 10 veces.

	◦ Cambiar aleatoriamente un elemento del vector y bloquearse durante 1 segundo. Esta
		operación se ha de repetir 100 veces.

	◦ Sumar   todos   los   elementos   del   vector,   mostrar   la   suma   por   pantalla   y   luego
		bloquearse durante 1 segundo. Esta operación se ha de repetir 5 veces.

3. El vector es inicialmente rellenado por el proceso padre con valores aleatorios.

*/


//Este es un ejercicio de procesos asi que tendre que utilizar una serie de bibliotecas especificas
//APRENDERME LAS LIBRERIAS QUE NECESITARE PARA HACER TODO ESTO


#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h> //para hacer referencia a los segundos con la funcion sleep
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>


/* 

De todas la librerias utilizadas encomtramos 4 que son de llamadas al sistema sys que serviran
para utilizar distintas funciones de los procesos, tenemos la libreria de unistd que si no
me equivoco el para el modo nucleo del pc, y por utimo tenemos las librerias basicas utilizadas
que son la stdio, la stdlib y la math para ciertas operaciones matematicas

*/

#define HIJOS 3
#define iter1 10
#define iter2 100
#define iter3 5

#define ok 77


int main(){

key_t key;
int status;
int *vector;
int indice;
int valor;
int suma=0;
srand(time(NULL));

// 1. Generar la clave ftok()

key = ftok("p1.c", 23);//he puesto 23 como podia haber puesto cualquier otra cosa

// 2. Reservar memoria compartida (comprobacion de la generacion de la clave) shmget()

int shmid = shmget(key, 100*sizeof(int), IPC_CREAT | 0700);

	if(shmid == -1){
		//printf("Error al generar la clave\n");
		fprintf(stderr, "Error al compartir memoria\n");
		exit(-1);
	}

// 3. Dirrecionar un puntero a la memoria reservada shmat()

vector = (int*) shmat(shmid, NULL, 0);

// 4. Operar con la memoria compartida (en un principio empezaremos generando 3 hijos) fork()

	for(int i=0; i<iter2; i++){
		valor = rand()%101;
		vector[i] = valor;
	}

	if(!fork()){
		printf("\nHijo 1 creado\n");

		for(int i=0; i<iter1; i++){
			printf("Introduzca el indice del vector: ");
			scanf("%d", &indice);

			printf("Intriduzca el valor del vector: ");
			scanf("%d", &valor);

			printf("\n");

			if( (indice<0)||(indice>99) ){
				printf("Error el indice o el valor introducido no es valido\n");
				exit(-1);
			}

			vector[indice] = valor;
		}

		exit(ok);
	}

	if(!fork()){
		printf("\nHijo 2 creado\n");

		for(int i=0; i<iter2; i++){
			indice = rand()%100;
			valor = rand()%101;

			vector[indice] = valor;
			sleep(1);
		}

		exit(ok);
	}


	if(!fork()){
		printf("\nHijo 3 creado\n");

		for(int i=0; i<iter3; i++){
			suma=0;

			for(int j=0; j<iter2; j++){
				suma = suma + vector[j];
			}
			printf("El valor de la suma es: %d\n", suma);
			sleep(1);
		}

		exit(ok);
	}


// 5. El padre espera la finalizacion de los hijos como tenemos varios hijos tenemos que hacerlo con un for

for (int i=0; i<HIJOS; i++){
	pid_t pid = wait(&status);
	printf("\nHijo %d termino con estado %d\n", pid, WEXITSTATUS(status) );
	//el WEXITSTATUS devuelve el valor de Ok que es 777 que significa que ha finalizado correctamente
}

// 6. Liberamos memoria compartida shmdt()

shmdt(vector);

// 7. Borramos memoria compartida shmctl()

shmctl (shmid, IPC_RMID, NULL);

return 0;
}