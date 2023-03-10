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
#include <ctype.h>
#include "file.h"
#include "statistic.h"

#define MAX_NAME_LEN 384 //nome del file o linghezza totale del path?
#define SHM_NAME "/shmlluperini5"
#define CORRECT_SINTAX_MSG(name) printf("The correct syntax is:\n\t%s <directory> <n. worker> <dim. buffer>\n", name);

#define NPRINTF(s, n)\
	for(int i = 0; i < n; i++) {\
		printf("%s", s);\
	}\
	printf("\n");

#define PRINT_HEADER()\
	printf("%-10s %-10s %-10s %-20s\n", "n", "avg", "std", "file");\
	NPRINTF("-", 50);

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) { perror((msg)); exit(EXIT_FAILURE);}

static bool issize(char* str) {
	while (*str) {
		if (!isdigit(*str)) return false;
		str++;
	}
	return true;
}

int main(int argc, char* argv[]) {
	char* path;
	size_t W;
	size_t N;
	char** bb;
	size_t bbsize;
	sem_t* mutex;
	sem_t* empty;
	sem_t* full;

	// Checking argc, arv[2] and argv[3] and than assgning path, W and N
	if (argc != 4) {
		CORRECT_SINTAX_MSG(argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		path = argv[1];

		if (!issize(argv[2])) {
			fprintf(stderr, "%s is not a valid size!\n", argv[2]);
			exit(EXIT_FAILURE);
		}
		sscanf(argv[2], "%lu", &W);
		
		if (!issize(argv[3])) {
			fprintf(stderr, "%s is not a valid size!\n", argv[3]);
			CORRECT_SINTAX_MSG(argv[0]);
			exit(EXIT_FAILURE);
		}
		sscanf(argv[3], "%lu", &N);
	}

	printf("path: %s\nW: %lu\nN: %lu\n", path, W, N);

	// Creation of the bounded buffer
	bbsize = (N+2) * sizeof(char) * MAX_NAME_LEN;
	int fd = shm_open(SHM_NAME, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	EXIT_ERROR(fd, -1, "Error shm_open");
	EXIT_ERROR(ftruncate(fd, bbsize), -1, "Error ftruncate");
	close(fd);
	bb = mmap(NULL, bbsize, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
	EXIT_ERROR(mutex, MAP_FAILED, "Error mmap");

	// Creation of the three semaphores 
	mutex = mmap(NULL, sizeof(sem_t),
			PROT_READ|PROT_WRITE,
			MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(mutex, MAP_FAILED, "Error mmap");
	sem_init(mutex, 1, 1);

	shm_unlink(SHM_NAME);
	return EXIT_SUCCESS;
}
