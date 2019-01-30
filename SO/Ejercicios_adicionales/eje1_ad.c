#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NHILOS 3

//producto de una matriz 3x3 por un vector 3x1 el producto se hace como fila por columna
int matrix[3][3]={{1,2,3},{4,5,6},{7,8,9}};
int vector[3]={1,2,1};
void *multiplica(void *p);

int main(){
pthread_t hilos[NHILOS];
int status, vpadre[NHILOS];
double retorno;//se qeu el fallo comienza desde aqui. ¿Tendre que hacer aqui otro malloc?

for(int i=0; i<NHILOS; i++){
	vpadre[i]= i;
	if (status = pthread_create(&hilos[i], NULL, multiplica, (void*) &vpadre[i])){
		exit(status);
	}
}


for(int j=0; j<NHILOS; j++){
	pthread_join(hilos[j], (void**) &retorno);
	printf("Valor retornado por el hilo %lu thread: %lf\n", hilos[j], *retorno);
}

return 0;
}

void *multiplica(void *p){
	extern int matrix[3][3];
	extern int vector[3];
	int *retorno;
	int suma=0;
	int *id;
	id = (int*)p;

	retorno = malloc(3*sizeof(int));
	
	for(int i=0; i<NHILOS; i++){//faltaria mostrar el vector, no entiendo como tres hilos se reparten tanto las tres filas de la matriz como la fila del vector
		printf("Fila de la matriz:\n");
		printf("[%d]\t", matrix[*id][i]);
	}

	for(int j=0; j<NHILOS; j++){
		for(int k=0; k<NHILOS; k++){
			suma= suma+(matrix[*id][j]*vector[j]);//tengo dudas aqui porque un hilo tiene que acceder al maldito vector
		}
		retorno[j]=suma;
	}


	pthread_exit((void*) retorno);
}

/*
1. Realice la multiplicación en paralelo de una matriz de 3x3 por un vector de 3x1. 
Para ello cree tres hebras que se repartan las filas de la matriz y del vector. 
Cada hijo debe imprimir la fila que le ha tocado y el resultado final de la multiplicación la cual además envía al padre. 
El padre debe esperar por la terminación de cada hijo y mostrar el vector resultante.
*/