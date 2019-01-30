#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ok 17

int main(int argc, char** argv){

	if(argc!=2){
		printf("No se introdujo el numero de procesos a crear\n");
		exit(-1);
	}

int n_procesos, status;
key_t key;
int shmid;
int *puntero;
pid_t pid;
int suma=0;

n_procesos = atoi(argv[1]);

	key = ftok("procesos.c", 23);

	if( ( shmid = shmget(key, sizeof(int), IPC_CREAT | 0700) ) == -1 ){
		printf("Error al reservar memoria compartida\n");
		exit(-1);
	}

	puntero = (int*) shmat(shmid, NULL, 0);

	pid = fork();

	if(pid){
		//no hago nada
	}

	else{
		suma = suma + getpid();
	}

	for(int i=0; i<n_procesos; i++){
		if (pid){//proceso padre
			printf("Padre con pid : %d\n", getpid());
		}

		else{// tengo que coger la ultima cifra del pid
			printf("Hijo con pid: %d\n", getpid());
			suma = suma + getpid();
			pid = fork();
			sleep(3);
			exit(ok);
		}
	}


	for (int i=0; i<n_procesos; i++){
		pid = wait(&status);
		printf("\nHijo %d termino con estado %d\n", pid, WEXITSTATUS(status));
	}

	shmdt(puntero);
	shmctl(shmid, IPC_RMID, NULL);

return 0;
}