/*

1. Compilar y ejecutar el programa hilos.c.

    1.1. Leer y reflexionar sobre las diferencias entre procesos e hilos.

    1.2. Comprobar que el resultado de la suma no es correcto e identificar 
        la sección crítica del programa.

2. Modificar el programa para que ahora se ejecuten 4 hilos y aplicar el algoritmo 
    de Lamport para resolver el problema de la sección crítica del programa.

3. Los hilos productores generan números aleatorios en el intervalo [0,1000] y los 
    depositan en el búfer limitado de tamaño N. Los hilos consumidores leen los 
    números depositados en el búfer y realizan las sumas sucesivas de los números 
    leídos. Para comprobar la corrección de la solución programada los productores 
    realizarán las sumas de los números que producen para comprobar si las sumas coinciden 
    con las de los consumidores.

    • Solucionar   el   problema   de   programación   concurrente   según   las   siguientes
    formulaciones:

    3.1. Hay un único hilo productor y un único hilo consumidor.

    3.2. Hay P hilos productores y C hilos consumidores. Cada número generado por un
        productor es consumido por un único consumidor. Esta es la formulación estándar del
        problema del productor consumidor.

    3.3. Hay un hilo productor y C hilos consumidores. Cada número generado por el
        productor ha de ser consumido por TODOS los hilos consumidores.

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h> //intervalo entre 0 y 1000

//semaforos mutex: semaforo binario, con valores 0/1 (cerrado/abierto)
//semaforos contadores: semaforos generales que toman valores de 0 a N

#define NBUFFER 5
#define NHILOS 2


int buffer[NBUFFER];
sem_t mutex_s; //semaforo binario para la seccion critica
sem_t n; //semaforor general para el consumidor. Cuenta los espacios ocupados
sem_t e;//semaforo general para el productor. Cuneta los espacios libres
int indice_p=0;
int indice_c=0;

void *productor(void *p);
void *consumidor(void *p);
void producir(int *numero);
void anadir(int numero);
void extraer(int *numero);


int main(){

int status, padre[NHILOS];
pthread_t hilos[NHILOS];
int *retorno;
srand(time (NULL));

void *productor(void *);
void *consumidor(void *);

extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;

sem_init(&mutex_s, 0, 1);
sem_init(&n, 0, 0);
sem_init(&e, 0, NBUFFER);


// Creaccion de los hilos

for(int i=0; i<NHILOS; i++){
    padre[i]=i;

    if(i==0){ // Para el hilo productor
        if( status = pthread_create(&hilos[i], NULL, productor, (void*) &padre[i] ) ){
            exit(status);
        }
    }

    else{ // Para el hilo consumidor
        if ( status = pthread_create(&hilos[i], NULL, consumidor, (void*) &padre[i] ) ){
            exit(status);
        }
    }
}



// Espera a la finalizacion de los hilos

for (int i=0; i<NHILOS; i++){
    pthread_join(hilos[i], (void**) &retorno);//espero al hilo productor

    if(i==0){
        printf("El valor de la suma del productor es: %d\n", *retorno);
    }

    else{
        printf("El valor de la suma del consumidor es: %d\n", *retorno);
    }
}

//en este caso no tengo unj resultado final como tal ya quemi resultado seria comprobar que ambas sumas sean iguales

return 0;
}

void *productor(void *p){
extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;
extern int indice_p;

int suma=0;
int numero;
int *retorno;

    for (int i=0; i<100; i++){

        producir(&numero); // Generar un numero aleatorio
        sem_wait(&e); // Un espacio libre menos. Si e<0 me bloqueo
        sem_wait(&mutex_s); // Entrar critica

            anadir(numero); // Poner en el buffer el valor generado
            suma = suma + numero;
            indice_p++;

            /*printf("\nBuffer productor: ");
            for (int j=0; j<NBUFFER; j++){
                printf("[%d] ", buffer[j]);
            }*/

            if (indice_p==NBUFFER){
                indice_p=0;
            }

        sem_post(&mutex_s); // Salir critica
        sem_post(&n); // Un espacio mas ocupado por un dato
        
    }

   //printf("\n");


    retorno= malloc(sizeof(int));
    *retorno = suma;
    pthread_exit( (void*) retorno );


}

void *consumidor(void *p){
extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;
extern int indice_c;
    
int suma=0;
int numero=0;
int *retorno;

    for (int i=0; i<100; i++){

        sem_wait(&n); // Un espacio menos ocupado, si n<0 me bloqueo
        sem_wait(&mutex_s); // Entrar critica

            extraer(&numero);
            suma = suma + numero;
            indice_c++;

            /*printf("\nBuffer consumidor: ");
            for (int j=0; j<NBUFFER; j++){
                printf("[%d] ", buffer[j]);
            }*/

            if( indice_c == NBUFFER ){
                indice_c = 0;
            }

        sem_post(&mutex_s); // Salir critica
        sem_post(&e); // Un espacio libre mas
        
    }

    //printf("\n");

    retorno = malloc(sizeof(int));
    *retorno = suma;
    pthread_exit( (void*) retorno );

}

void producir(int *numero){
    *numero = rand()%1001;//numero entre 0 y 1000
}

void anadir(int numero){
extern int buffer[NBUFFER];
extern int indice_p;

    buffer[indice_p]=numero;
}

void extraer(int *numero){
extern int buffer[NBUFFER];
extern int indice_c;
    
    *numero = buffer[indice_c];
    buffer[indice_c] = 0;
}