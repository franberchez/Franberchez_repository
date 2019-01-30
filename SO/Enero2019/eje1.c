#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int n;
void sumar(int numero);


int main(int argc, char** argv){
extern int n;

	if(argc!=2){
		printf("No se introdujo el numero de procesos a crear\n");
		exit(-1);
	}

n = atoi(argv[1]);

int shmid;
key_t key;
int *puntero;
pid_t pid;

key = ftok("eje1.c", 23);

	if( (shmid = shmget(key, sizeof(int), IPC_CREAT | 0700))==-1 ){
		printf("Error al reservar memoria\n");
		exit(-1);
	}

puntero = (int*) shmat(shmid, NULL, 0);

	for(int i=0; i<n; i++){
		pid = fork();

		if(pid){//Proceso padre
			//printf("Padre con pid: %d\n", getpid());
		}

		else{
			sumar(i);
		}

		//sleep(2);
	}

	shmdt(puntero);
	shmctl(shmid, IPC_RMID, NULL);

return 0;
	
}


void sumar(int numero){
	int aux;
	aux = getpid()%10;

	int childpid, status;

	while ( (childpid = wait(&status))>0 ){
		if(WIFEXITED(status)){
			aux = aux + WEXITSTATUS(status);
		}

		/*else{
			if(WIFSIGANALED(status)){
				printf("PID: %d signaled, status = %d\n", childpid, status);
			}
		}

		else{
			if(WIFSTOPPED(status)){
				printf("PID: %d stopped, status = %d\n", childpid, status);
			}
		}*/

		printf("ITERACION: %d. PID: %d. PID PADRE: %d. Valor recibido: %d\n", numero, getppid(), WEXITSTATUS(status));
		exit(aux);
	}
}