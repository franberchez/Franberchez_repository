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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NBUFFER 5
#define HILOS_P 2
#define HILOS_C 4

int buffer[NBUFFER];
sem_t mutex_s; // semaforo binario para las seccion critica
sem_t n; // semaforo general para el consumidor. Cuenta los espacios ocupados
sem_t e; // /*tamaño del buffer*/ semaforo general para el productor. Cuenta los espacios libres
int indice_p = 0;
int indice_c = 0;
int suma_p = 0;
int suma_c = 0;

void *productor(void *p);
void producir(int *numero);
void anadir(int numero);
void *consumidor(void *p);
void extraer(int *numero);


int main(){
extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;
extern int suma_p;
extern int suma_c;

pthread_t hilos_p[HILOS_P], hilos_c[HILOS_C];
int status, padre_p[HILOS_P], padre_c[HILOS_C];
void *productor (void *);
void *consumidor (void *);
srand(time (NULL));

    sem_init(&mutex_s, 0, 1);
    sem_init(&n, 0, 0);
    sem_init(&e, 0, NBUFFER);

// Creo los hilos productores

    for (int i=0; i<HILOS_P; i++){
        padre_p[i]=i;

        if( (status = pthread_create(&hilos_p[i], NULL, productor, (void*) &padre_p[i])) ){
            exit(status);
        }
    }

// Creo los hilos consumidores

    for (int i=0; i<HILOS_C; i++){
        padre_c[i] = i;

        if( (status = pthread_create(&hilos_c[i], NULL, consumidor, (void*) &padre_c[i])) ){
            exit(status);
        }
    }

// Espero los hilos productores

    for(int i=0; i<HILOS_P; i++){
        pthread_join(hilos_p[i], NULL);
    }
    printf("Suma de los productores: %d\n", suma_p);

// Espero los hilos productores

    for (int i=0; i<HILOS_C; i++){
        pthread_join(hilos_c[i], NULL);
    }
    printf("Suma de los consumidores: %d\n", suma_c);

return 0;
}

void *productor(void *p){
extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;
extern int suma_p;
extern int indice_p;

int numero;

    for (int i=0; i<200; i++){

        producir(&numero); // Genero un numero aleatorio
        sem_wait(&e); // Un espacio libre menos. Si e<0 me bloqueo
        sem_wait(&mutex_s); // Entrar critica

            anadir(numero);
            suma_p = suma_p + numero;
            indice_p++;

            if(indice_p == NBUFFER){
                indice_p = 0;
            }

        sem_post(&mutex_s); // Salir critica
        sem_post(&n); // Un espacio mas ocupado por un dato generado
    }

}

void *consumidor(void *p){
extern sem_t mutex_s;
extern sem_t n;
extern sem_t e;
extern int suma_c;
extern int indice_c;

int numero;

    for (int i=0; i<100; i++){

        sem_wait(&n); // Un espacio menos ocupado, si n<0 me bloqueo
        sem_wait(&mutex_s); // Entrar critica

            extraer(&numero);
            suma_c = suma_c + numero;
            indice_c++;

            if(indice_c == NBUFFER){
                indice_c = 0;
            }

        sem_post(&mutex_s); // Salir critica
        sem_post(&e); // Un espacio libre mas
    }


}

void producir(int *numero){
    *numero = rand()%1001;
}

void anadir(int numero){
extern int buffer[NBUFFER];
extern int indice_p;

    buffer[indice_p] = numero;
}

void extraer(int *numero){
extern int buffer[NBUFFER];
extern int indice_c;
    
    *numero = buffer[indice_c];
    buffer[indice_c] = 0;
}