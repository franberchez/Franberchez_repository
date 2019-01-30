#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t s; // semaforo binario para controlar la seccion critica
int nhilos;
int v[10]={0,0,0,0,0,0,0,0,0,0};


int main(int argc, char** argv){
extern sem_t s;
extern int nhilos;
extern int v[10];
int suma=0;
int suma_vector=0;

	if(argc!=2){
		printf("No se introdujo el numero de hilos\n");
		exit(-1);
	}

	nhilos = atoi(argv[1]);

sem_init(&s, 0, 1);

int padre[nhilos], status;
pthread_t hilos[nhilos];
int *retorno;
void *vector (void*);
srand(time (NULL));

	for(int i=0; i<nhilos; i++){
		padre[i]=i;

		if( (status = pthread_create(&hilos[i], NULL, vector, (void*) &padre[i] ) ) ){
			exit(status);
		}
	}

	for(int i=0; i<nhilos; i++){
		pthread_join(hilos[i], (void**) &retorno);
		suma = suma + *retorno;
	}

	printf("El valor de la suma devuelta es = %d\n", suma);

	for(int i=0; i<10; i++){
		suma_vector = suma_vector + v[i];
	}

	printf("El valor de la suma del vector es = %d\n", suma_vector);

return 0;
}

void *vector (void *p){
extern sem_t s;
extern int v[10];

int suma=0;
int valor, indice;
int *retorno;

	for(int i=0; i<100; i++){
			
		sem_wait(&s);

		valor = rand()%101;
		indice = rand()%10;
		suma = suma + valor;
		v[indice] = valor;

		sem_post(&s);

		//sleep(1);

	}

	retorno = malloc(sizeof(int));
	*retorno = suma;
	pthread_exit( (void*) retorno);



}