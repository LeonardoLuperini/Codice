#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

void put(int n, int* bb, int* head, int* tail, int N, sem_t* mutex, sem_t* full, sem_t* empty) {

}

int get(int* bb, int* head, int* tail, int N, sem_t* mutex, sem_t* full, sem_t* empty) {
	int n = 0;
	return n;
}


void produttore(int* bb, int* head, int* tail, int N, sem_t* mutex, sem_t* full, sem_t* empty)) {
	printf("produttore %d inizia\n", getgid());

}

void consumatore(int* bb, int* head, int* tail, int N, sem_t* mutex, sem_t* full, sem_t* empty) {

}

int main(void) {
	int N = 5; //Dim buffer
	int C = 3; //Numero consumatori
	srand(time(NULL));

	//creazione SMS
	char* shmName = "/shmEsercizioProva";
	int fd = shm_open(shmName, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	ftruncate(fd, (N+2)*sizeof(int)); //N elementi più head e tail pointer
	
	//memory mapping
	int* bb = mmap(NULL, (N+2)*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	int* head = bb+N;
	int* tail = bb+N+1;
	*head = *tail = 0;
	close(fd);

	//sem_t* mutex=mmap

	shm_unmap
	for(int i = 0; i < C; i++) {
		int pid = fork();
		if(pid == 0) {
			consumatore();
			return EXIT_SUCCESS;
		}
	}
	
	produttore();

	for(int i = 0; i < C; i++) {
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
