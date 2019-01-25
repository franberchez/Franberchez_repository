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
		bloquearse durante 30 segundos. Esta operación se ha de repetir 5 veces.

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


/* 

De todas la librerias utilizadas encomtramos 4 que son de llamadas al sistema sys que serviran
para utilizar distintas funciones de los procesos, tenemos la libreria de unistd que si no
me equivoco el para el modo nucleo del pc, y por utimo tenemos las librerias basicas utilizadas
que son la stdio, la stdlib y la math para ciertas operaciones matematicas

*/

#define HIJOS 3
#define ok 77

int main(){

key_t key;
int status;

// 1. Generar la clave ftok()

key = ftok("p1.c", 23);//he puesto 23 como podia haber puesto cualquier otra cosa

// 2. Reservar memoria compartida (comprobacion de la generacion de la clave) shmget()

int shmid = shmget(key, sizeof(int), IPC_CREAT | 0700);

	if(shmid == -1){
		//printf("Error al generar la clave\n");
		fprintf(stderr, "Error al compartir memoria\n");
		exit(-1);
	}

// 3. Dirrecionar un puntero a la memoria reservada shmat()

int *puntero = (int*) shmat(shmid, NULL, 0);

// 4. Operar con la memoria compartida (en un principio empezaremos generando 3 hijos) fork()

	for(int i=0; i<HIJOS; i++){
		if(!fork()){
			printf("\nHijo %d creado\n", i);
			exit(ok);
		}
	}


// 5. El padre espera la finalizacion de los hijos como tenemos varios hijos tenemos que hacerlo con un for

for (int i=0; i<HIJOS; i++){
	pid_t pid = wait(&status);
	printf("\nHijo %d termino con estado %d\n", pid, WEXITSTATUS(status) );
	//el WEXITSTATUS devuelve el valor de Ok que es 777 que significa que ha finalizado correctamente
}

// 6. Liberamos memoria compartida shmdt()

shmdt(puntero);

// 7. Borramos memoria compartida shmctl()

shmctl (shmid, IPC_RMID, NULL);

return 0;
}