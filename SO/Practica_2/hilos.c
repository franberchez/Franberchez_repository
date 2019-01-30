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
#include <unistd.h>
#include <stdlib.h>

double counter = 0;

#define ITER	1000
#define NHILOS	3

int main() //thread == hilo es una simple nomenclatura para tenerlo claro
{
    pthread_t hilos[NHILOS]; 
//variable de tipo hilo para crear los hilos es un vector de hilos para indicar que tengo 3 (ID)
    int status, i, v[NHILOS]; 
//status es como shmid en procesos. v[NHILOS] puntero al parametro que se le pasara a la funcion
    extern double counter;
//variable compartida counter
    void *adder(void *);
//adder es la direccion de memoria de la funcion que queremos que ejecute el hilo
//la funcion devuelve un puntero a void y como parametro otro puntero generico (casting void*)
    double *r_value;
//valor de retorno

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	v[i] = i;
	if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i]))) //definido en el doc
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value); //definido en el doc
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *adder(void *p)
{
    double l, *to_return;
//l variable a la que vamos a igualar la varible compartida counter de tipo double
//variable de retorno para no perder la info del hilo (RESERVA DE MEMORIA FAMOSA)
    extern double counter;
//variable compartida counter
    int *id, i;
//*id es una referencia a la ID del hilo que llega a la funcion

    id = (int *) p;

    for (i = 0; i < ITER; i++) {
//el counter final una vez pasen por aqui los 3 hilos debe ser 3000 ya que cada vez que pasa se le suma 1
	l = counter;
	fprintf(stdout, "Hilo %d: %f\n", *id, counter);
	l++;
	counter = l;
    }

// RESERVA DE MEMORIA FAMOSA y finalizacion del hilo con exit y esperado en el wait

    to_return = malloc(sizeof(double));

    *to_return = counter;

    pthread_exit((void *) to_return);
}
