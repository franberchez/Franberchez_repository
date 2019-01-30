#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NCLIENTES 3
#define NPROVEEDORES 2
#define NBUFFER 7

int buffer[NBUFFER];
sem_t s;


int main(){
extern sem_t s;
extern int buffer[NBUFFER];
pthread_t h_clientes[NCLIENTES], h_proveedores[NPROVEEDORES];
int padre_c[NCLIENTES], padre_p[NPROVEEDORES];
int status;
//int *retorno;
srand(time (NULL));

void *proveedor (void*);
void *cliente (void*);

printf("Buffer de coches antes de los hilos:\n\n");

	for(int i=0; i<NBUFFER; i++){
		buffer[i] = rand()%300;
		printf("Coche modelo %d tiene una cantidad en stock de %d\n", i, buffer[i]);
	}



sem_init(&s, 0, 1);

	for(int i=0; i<NCLIENTES; i++){
		padre_c[i] = i;

		if( (status = pthread_create(&h_clientes[i], NULL, proveedor, (void*) &padre_c[i] ) ) ){
			exit(status);
		}
	}

	for (int i=0; i<NPROVEEDORES; i++){
		padre_p[i] = i;

		if( (status = pthread_create(&h_proveedores[i], NULL, proveedor, (void*) &padre_p[i] ) ) ){
			exit(status);
		}
	}


	for(int i=0; i<NCLIENTES; i++){
		//pthread_join(h_clientes[i], (void**) &retorno);
		pthread_join(h_clientes[i], NULL);
	}

	for(int i=0; i<NPROVEEDORES; i++){
		//pthread_join(h_clientes[i], (void**) &retorno);
		pthread_join(h_clientes[i], NULL);
	}

printf("\n");
printf("Buffer de coches despues de los hilos:\n\n");

	for(int i=0; i<NBUFFER; i++){
		printf("Coche modelo %d tiene una cantidad en stock de %d\n", i, buffer[i]);
	}



return 0;
}

void *cliente(void *p){
extern int buffer[NBUFFER];
extern sem_t s;
int cantidad, modelo, tope;


	sem_wait(&s);

		modelo = rand()%7;
		tope = buffer[modelo]+1;
		cantidad = rand()%tope;
		tope = tope - cantidad -1;
		buffer[modelo] = cantidad;

	sem_post(&s);

	pthread_exit(NULL);


}

void *proveedor(void *p){
extern int buffer[NBUFFER];
extern sem_t s;
int cantidad, modelo, tope;

	sem_wait(&s);

		modelo = rand()%7;
		tope = buffer[modelo]+1;
		cantidad = rand()%tope;
		tope = tope + cantidad -1;
		buffer[modelo] = cantidad;

	sem_post(&s);

	pthread_exit(NULL);

}