// linearecursiva.c
// Un proceso crea un hijo, ese hijo crea otro hijo... (RECURSIVAMENTE)

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int creaprocesos(int nprocesos);

int main(int argc, char const *argv[])
{
	if (argc < 2) {
		printf("./a.out P\n");
		exit(EXIT_FAILURE);
	}

	int nprocesos;

	if((nprocesos = atoi(argv[1])) < 2) {
		printf("Error, debe crearse mas de 1 proceso\n");
		exit(EXIT_FAILURE);
	}

	creaprocesos(nprocesos);
}

int creaprocesos(int nprocesos) {
	if(nprocesos==1) { // ULTIMO HIJO
		printf("Father PID: %d Procces PID: %d\n\n", getppid(), getpid());
		exit(getpid()%10);
	} else {
		nprocesos--;
		if(fork()) { // ENTRAN LOS PADRES
			int status;
			sleep(3);
			pid_t childpid = wait(&status);
			printf("Child %d finished with status %d\n\n", childpid, WEXITSTATUS(status));
			printf("Father PID: %d Procces PID: %d Child PID: %d\n\n",
				getppid(), getpid(), childpid);
			exit((getpid()%10) + WEXITSTATUS(status));
		} else creaprocesos(nprocesos); // LOS HIJOS CREAN OTRO PROCESO
	}
}