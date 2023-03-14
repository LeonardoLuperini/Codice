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

#define MAX_NAME_LEN 384
#define STOP_SIGNAL "stop"
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

#define IS_WORKER(pid) (pid == 0)
#define IS_COLLECTOR(pid) (pid == 0)

typedef struct {
	sem_t 	full; 	//n. of element before bb is full
	sem_t 	empty; 	//n. of element before bb is empty
	sem_t 	mutex;
	size_t 	tail;
	size_t 	head;
	size_t 	len;
	char 	strings[][MAX_NAME_LEN];
} bb_t;

typedef struct {
	size_t n;
	double avg;
	double std;
	char path[MAX_NAME_LEN];
} data_t;

void put(char* str, bb_t* bb);
void get(char* str, bb_t* bb);
void scanfs(char* path, bb_t* bb);
void worker(bb_t* bb, int p[]);
void collector(int p[]);

static void get_cli_input(int argc, char** argv, char* path, size_t* W, size_t* N);
static bool str_is_size(char* str);
static bool readpipe(int fd, void* msg, size_t msglen);

int main(int argc, char* argv[]) {
	char path[MAX_NAME_LEN];
	size_t W;
	size_t N; //n. of element of bb
	bb_t* bb;
	pid_t pid;
	int p[2]; //pipe

	// Checking argc, argv[2] and argv[3] and than assgning path, W and N
	get_cli_input(argc, argv, path, &W, &N);

	// Creation of the bounded buffer
	// Pointer to the bounded buffer
	bb = mmap(NULL, sizeof(bb_t) + N * MAX_NAME_LEN * sizeof(char), PROT_WRITE|PROT_READ, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb, MAP_FAILED, "Error mmap");
	bb->len = N;
	bb->head = 0;
	bb->tail = 0;

	// Semaphores creation
	sem_init(&bb->mutex, 1, 1);
	sem_init(&bb->empty, 1, 0);
	sem_init(&bb->full, 1, N);

	// Exclusive pipe creation
	EXIT_ERROR(pipe(p), -1, "Error pipe");
	
	// Worker generation
	for (int i = 0; i < W; i++) {
		EXIT_ERROR(pid = fork(), -1, "Error fork");
		if IS_WORKER(pid) {
			worker(bb, p);
		}
	}

	// Collector generation
	EXIT_ERROR(pid = fork(), -1, "Error fork");
	if IS_COLLECTOR(pid) {
		collector(p);
	}

	//***************** SERVER *****************
	close(p[0]);
	close(p[1]);
	scanfs(path, bb);

	for (int i = 0; i < W; i++) {
		put(STOP_SIGNAL, bb);
	}
	//******************************************
	
	// Spring cleaning
	for (int i = 0; i < W + 1; i++) {
		wait(NULL);
	}
	
	sem_destroy(&bb->full);
	sem_destroy(&bb->empty);
	sem_destroy(&bb->mutex);
	munmap(bb, sizeof(bb_t) + N * MAX_NAME_LEN * sizeof(char));
	return EXIT_SUCCESS;
}

void scanfs(char* path, bb_t* bb) {
	DIR* d;
	struct dirent* file;
	char newpath[MAX_NAME_LEN];
	char* ext;

	EXIT_ERROR(d = opendir(path), NULL, "Error opendir");
	while ((errno = 0, file = readdir(d)) != NULL) {
		if IS_FILE(file) {
			ext = strrchr(file->d_name, '.');
			if (ext != NULL && strcmp(ext, ".dat") == 0) {
				concat_path(path, file->d_name, newpath);
				put(newpath, bb);
			}
		}
	}
	closedir(d);

	EXIT_ERROR(d = opendir(path), NULL, "Error opendir");
	while ((errno = 0, file = readdir(d)) != NULL) {
		if (NOT_PREV_DIR(file->d_name) && NOT_THIS_DIR(file->d_name) && IS_DIR(file)) {
			concat_path(path, file->d_name, newpath);
			scanfs(newpath, bb);
		}
	}
	closedir(d);
}

void worker(bb_t* bb, int p[]) {
	data_t d;
	double* numbers = NULL;
	size_t actual_len = 0;
	d.n = 0;

	// Valgrind cry if i don't do this
	for(int i = 0; i < MAX_NAME_LEN; i++) d.path[i] = '\0';

	close(p[0]);
	while (true) {
		d.n = 0;
		get(d.path, bb);
		if (!strcmp(d.path, STOP_SIGNAL)) break;
		file_to_array(d.path, &numbers, &actual_len, &d.n);
		d.avg = avg(numbers, d.n);
		d.std = std(numbers, d.n);
		EXIT_ERROR(write(p[1], &d, sizeof(data_t)), -1, "Error write");
	}
	if (numbers != NULL) free(numbers);
	close(p[1]);
	exit(EXIT_SUCCESS);
}

static bool readpipe(int fd, void* msg, size_t msglen) {
	bool eof = false;
	ssize_t res;
	size_t n = 0;

	do {
		res = read(fd, msg, msglen - n);
		CHECK_READ(res, eof, n);
	} while (n < msglen && !eof);	

	return eof;
}

void collector(int p[]) {
	data_t d;
	close(p[1]);

	PRINT_HEADER();

	while (true) {
		if (readpipe(p[0], &d, sizeof(data_t))) break;
		printf("%-5lu %-10lf %-10lf %-20s\n", d.n, d.avg, d.std, d.path);
		fflush(stdout);
	}
	
	close(p[0]);
	exit(EXIT_SUCCESS);
}

void put(char* str, bb_t* bb) {
	sem_wait(&bb->full);
	sem_wait(&bb->mutex);
	strcpy(bb->strings[bb->tail], str);
	bb->tail = (bb->tail + 1) % bb->len;
	sem_post(&bb->empty);
	sem_post(&bb->mutex);
}

void get(char* str, bb_t* bb) {
	sem_wait(&bb->empty);
	sem_wait(&bb->mutex);
	strcpy(str, bb->strings[bb->head]);
	bb->head = (bb->head + 1) % bb->len;
	sem_post(&bb->full);
	sem_post(&bb->mutex);
}

static bool str_is_size(char* str) {
	while (*str) {
		if (!isdigit(*str)) return false;
		str++;
	}
	return true;
}

static void get_cli_input(int argc, char** argv, char* path, size_t* W, size_t* N) {
	if (argc != 4) {
		CORRECT_SINTAX_MSG(argv[0]);
		exit(EXIT_FAILURE);
	}
	else {
		strcpy(path, argv[1]);

		if (!str_is_size(argv[2])) {
			fprintf(stderr, "%s is not a valid size!\n", argv[2]);
			CORRECT_SINTAX_MSG(argv[0]);
			exit(EXIT_FAILURE);
		}
		sscanf(argv[2], "%lu", W);
		if (*W == 0) {
			fprintf(stderr, "%s is not a valid size!\n", argv[2]);
			CORRECT_SINTAX_MSG(argv[0]);
			exit(EXIT_FAILURE);
		}
		
		if (!str_is_size(argv[3])) {
			fprintf(stderr, "%s is not a valid size!\n", argv[3]);
			CORRECT_SINTAX_MSG(argv[0]);
			exit(EXIT_FAILURE);
		}
		sscanf(argv[3], "%lu", N);
		if (*N == 0) {
			fprintf(stderr, "%s is not a valid size!\n", argv[2]);
			CORRECT_SINTAX_MSG(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

}
