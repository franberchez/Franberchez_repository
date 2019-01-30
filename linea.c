// linea.c
// Un proceso crea un hijo, ese hijo crea otro hijo...

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESOS 3

int main(int argc, char const *argv[])
{
	if(PROCESOS<2) {
		printf("Error, debe crearse mas de 1 proceso\n");
		exit(EXIT_FAILURE);
	}

	int status;

	for(int i=0; i<PROCESOS; i++) {

		if(i==PROCESOS-1) { // Ultimo hijo. Este no recoge a nadie
			printf("Father PID: %d Procces PID: %d\n", getppid(), getpid());
			exit((getpid()%10));
		}	// ^^^^ Por tanto no hay que sumar WEXITSTATUS porque no tiene hijos

		if(fork()) { // Solo entran los padres
			sleep(3);
			pid_t childpid = wait(&status); // Espera a recoger a su hijo
			printf("Child %d finished with status %d\n", childpid, WEXITSTATUS(status));
			printf("Father PID: %d Procces PID: %d Child PID: %d\n",
				getppid(), getpid(), childpid);
			exit((getpid()%10) + WEXITSTATUS(status));
			// Devuelve la ultima cifra de su PID más el resultado del hijo
			// anterior

			// Lo que ponemos en exit es lo que recoge el correspondiente
			// padre en la variable status al hacer el wait.
		}
	}
}