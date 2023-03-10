#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define C 7
#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) { perror((msg)); exit(EXIT_FAILURE);}
#define SON(pid) (pid == 0)
#define SHM_NAME "/shmlluperini5"

int main(void) {
	srand(time(NULL));
	
	pid_t pid;
	sem_t* sem;
	size_t* ptr_counter;

	int fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	EXIT_ERROR(fd, -1, "Error shm_open");
	EXIT_ERROR(ftruncate(fd, sizeof(size_t)), -1, "Error ftruncate");
	ptr_counter = mmap(NULL, sizeof(size_t), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	EXIT_ERROR(sem, MAP_FAILED, "Error mmap");
	(*ptr_counter) = 0;
	close(fd);

	sem = mmap(NULL, sizeof(sem_t),
			PROT_READ|PROT_WRITE,
			MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(sem, MAP_FAILED, "Error mmap");
	sem_init(sem, 1, 1);

	for (int i = 0; i < C; i++) {
		pid = fork();
		EXIT_ERROR(pid, -1, "Errore Fork");
		if SON(pid) {
			sleep(rand()%6);
			fprintf(stderr, "%d: Partito\n", getpid());
			sem_wait(sem);
			fprintf(stderr, "%d: HO IL POTEREEEE!\n", getpid());
			sleep(rand()%3);
			fprintf(stderr, "%d: Incremento il counter a %lu\n", getpid(), ++(*ptr_counter));
			sem_post(sem);
			return EXIT_SUCCESS;
		}
	}
	
	for (int i = 0; i < C; i++) {
		wait(NULL);
	}
	fprintf(stderr, "counter: %lu\n", (*ptr_counter));

	munmap(sem, sizeof(sem));
	munmap(ptr_counter, sizeof(size_t));
	shm_unlink(SHM_NAME);
	sem_destroy(sem);
	return EXIT_SUCCESS;
}
