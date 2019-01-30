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
#include <stdbool.h>


#define ITER 1000
#define NHILOS 4

bool eligiendo[NHILOS]={false, false, false, false};
int numero[NHILOS]={0,0,0,0};
double counter = 0;

void *adder(void *p);
int max(int numero[]);

int main(){

pthread_t hilos[NHILOS];
void *adder(void *);
double *r_value;
int status, v[NHILOS];
extern double counter;

// Creaccion de los hilos

for (int i=0; i<NHILOS; i++){
    v[i]=i;
    if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i]))){
        exit(status);
    }
}


// Espera a la finalizacion de los hilos

for (int i=0; i<NHILOS; i++){
    pthread_join(hilos[i], (void**) &r_value);
    printf("Vlue returned by %lu thread: %lf\n", hilos[i], *r_value);
}

// Resultado final

fprintf(stdout, "%f\n", counter);

return 0;
}

void *adder(void *p){

extern double counter;
extern bool eligiendo[NHILOS];
extern int numero[NHILOS];

double l, *to_return;
int *id;
id = (int *)p;
    
    for(int j=0; j<NHILOS; j++){

        eligiendo[*id] = true;
        numero[*id] = max(numero)+1;
        eligiendo[*id] = false;

            for(int k=0; k<NHILOS; k++){
                while(eligiendo[k]);
                while ( (numero[k] != 0) && ( (numero[k]<numero[*id]) || ( (numero[k]==numero[*id]) && (k<(*id)) ) ) );
            }

            //EMPIEZA CRITICA

            for (int i=0; i<ITER; i++){
                l = counter;
                fprintf(stdout, "Hilo %d: %f\n", i, counter);
                l++;
                counter = l;
            }

            //FINALIZA CRITICA

        numero[*id]=0;
        
        to_return = malloc(sizeof(double));
        *to_return = counter;
        pthread_exit( (void*) to_return);
    }

}


int max(int numero[]){
int valor = 0;

    for(int i=0; i<NHILOS; i++){
        if(valor < numero[i]){
            valor = numero[i];
        }
    }

    return valor;
}