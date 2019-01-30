#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int N;
int M;
/*int *v1;
int *v2;*/

struct parametros{
	int *vector1;
	int *vector2;
	int tam;
};

void *producto_escalar(struct parametros *aux);

int main(){
extern int N;
extern int M;
/*extern int *v1;
extern int *v2;*/

	printf("\nIntroduzca el tamano del vector: ");
	scanf("%d", &N);

	printf("\nIntroduzca el numero de hilos: ");
	scanf("%d", &M);

	if(M > N){
		printf("Error el numero de hilos es mayor que el tamano del vector\n");
		exit(-1);
	}

pthread_t hilos[M];
int status;
//int padre[M];
int *retorno;
//void *producto_escalar (void*);
srand(time (NULL));

int v1[N], v2[N];

/*v1 = malloc(N*sizeof(int));
v2 = malloc(N*sizeof(int));*/

	for(int i=0; i<N; i++){
		v1[i] = rand()%10;
		v2[i] = rand()%10;
	}

int num = N/M;// para saber cuantos elementos del vector le toca a cada hilo
int resto = N%M;// por si el resto no fuese 0 sumarle al tamaño del ultimo hilo lo que quede de resto
struct parametros aux[M];

	for(int i=0; i<M; i++){
		if (i == M-1){
			aux[i].vector1 = &v1[i];
			aux[i].vector2 = &v2[i];
			aux[i].tam = num + resto;
		}

		else{
			aux[i].vector1 = &v1[i];
			aux[i].vector2 = &v2[i];
			aux[i].tam = num;
		}

		if( (status = pthread_create(&hilos[i], NULL, (void*) producto_escalar, (void*) &aux[i]) ) ){
			printf("Error al reservar memoria\n");
			exit(status);
		}
	}

int suma = 0;

	for(int i=0; i<M; i++){
		pthread_join(hilos[i], (void**) &retorno);
		suma = suma + *retorno;
	}

	printf("EL valor del producto escalar es = %d\n", suma);

}

void *producto_escalar(struct parametros *aux){

int *retorno;
int suma = 0;

	for (int i=0; i<aux->tam; i++){
		suma += aux->vector1[i] * aux->vector2[i];
	}

retorno = malloc(sizeof(int));
*retorno = suma;
pthread_exit((void*) retorno);
	
}