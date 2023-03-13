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

#define MAX_NAME_LEN 384 //nome del file o linghezza totale del path? E' anche in file.h
#define SHM_NAME "/shmlluperini5" //LO UTULIZZO ANCORA?!?!?!?!?!?
#define STOP_SIGNAL "stop"
#define CORRECT_SINTAX_MSG(name) printf("The correct syntax is:\n\t%s <directory> <n. worker> <dim. buffer>\n", name);
#define loop while (1)

#define NPRINTF(s, n)\
	for(int i = 0; i < n; i++) {\
		printf("%s", s);\
	}\
	printf("\n");

#define PRINT_HEADER()\
	printf("%-10s %-10s %-10s %-20s\n", "n", "avg", "std", "file");\
	NPRINTF("-", 50);

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) { perror((msg)); exit(EXIT_FAILURE);}

#define WORKER(pid) (pid == 0)
#define COLLECTOR(pid) (pid == 0)

typedef struct {
	sem_t* 	full; 	//n. of element before bb is full
	sem_t* 	empty; 	//n. of element before bb is empty
	sem_t* 	mutex;
	size_t* tail;
	size_t* head;
	size_t 	len;
	char 	strings[][MAX_NAME_LEN];
} bb_t;


void put(char* str, bb_t* bb) {
	sem_wait(bb->full);
	sem_wait(bb->mutex);
	strcpy(bb->strings[*bb->tail], str);
	*bb->tail = (*bb->tail + 1) % bb->len;
	//fprintf(stderr, "Ho inserito: %s\n", str);
	sem_post(bb->empty);
	sem_post(bb->mutex);
}

void get(char* str, bb_t* bb) {
	//fprintf(stderr, "worker (%d): sono nel get\n", getpid());
	sem_wait(bb->empty);
	sem_wait(bb->mutex);
	strcpy(str, bb->strings[*bb->head]);
	*bb->head = (*bb->head + 1) % bb->len;
	sem_post(bb->full);
	sem_post(bb->mutex);
}

void scanfs(char* path, bb_t* bb);

void file_to_array(char* path, double* numbers, size_t* actual_len, size_t* index) {
	FILE* f;
	char* linebuf = NULL;
	char* test = NULL;
	size_t linelen = 0;
	int resgetline;

	EXIT_ERROR(f = fopen(path, "r"), NULL, "Error fopen");
	for (*index = 0; !feof(f);) {
		CHECK_GETLINE(resgetline = getline(&linebuf, &linelen, f));
		if (resgetline == -1) break;	
		if (*index == *actual_len) {
			numbers = reallocarray(numbers, *actual_len += 2, sizeof(double));
			EXIT_ERROR(numbers, NULL, "Error realloc");
		}
		numbers[(*index)] = strtod(linebuf, &test);
		if (numbers[(*index)] != 0 && linebuf != test) (*index)++;
	}
	if (linebuf != NULL) free(linebuf);
	fclose(f);
}

void worker(bb_t* bb) {
	char filepath[MAX_NAME_LEN];
	double* numbers = NULL;
	size_t actual_len = 0;
	size_t len = 0;

	fprintf(stderr, "Ciao sono il worker n. %d\n", getpid());
	loop {
		len = 0;
		get(filepath, bb);
		if (!strcmp(filepath, STOP_SIGNAL)) break;
		fprintf(stderr, "worker (%d): il path che ho letto è %s\n", getpid(), filepath);
		file_to_array(filepath, numbers, &actual_len, &len);
	}
	if (numbers != NULL) free(numbers);
	exit(EXIT_SUCCESS);
}

static bool str_is_size(char* str) {
	while (*str) {
		if (!isdigit(*str)) return false;
		str++;
	}
	return true;
}

void static get_cli_input(int argc, char** argv, char* path, size_t* W, size_t* N);

int main(int argc, char* argv[]) {
	char path[MAX_NAME_LEN];
	size_t W;
	size_t N; //n. of element of bb
	bb_t* bb;
	pid_t pid;

	// Checking argc, arv[2] and argv[3] and than assgning path, W and N
	get_cli_input(argc, argv, path, &W, &N);

	// Creation of the bounded buffer
	// Pointer to the bounded buffer
	bb = mmap(NULL, sizeof(bb_t) + N * MAX_NAME_LEN * sizeof(char), PROT_WRITE|PROT_READ, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb, MAP_FAILED, "Error mmap");
	bb->len = N;
		
	// Pointer to the head of bb
	bb->head = mmap(NULL, sizeof(size_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb->head, MAP_FAILED, "Error mmap")
	*bb->head = 0;

	// Pointer to the tail of bb
	bb->tail = mmap(NULL, sizeof(size_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb->tail, MAP_FAILED, "Error mmap")
	*bb->tail = 0;

	
	// Creation of the three semaphores 
	bb->mutex = mmap(NULL, sizeof(sem_t),
			PROT_READ|PROT_WRITE,
			MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb->mutex, MAP_FAILED, "Error mmap");
	sem_init(bb->mutex, 1, 1);

	bb->empty = mmap(NULL, sizeof(sem_t),
			PROT_READ|PROT_WRITE,
			MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb->empty, MAP_FAILED, "Error mmap");
	sem_init(bb->empty, 1, 0);
	
	bb->full = mmap(NULL, sizeof(sem_t),
			PROT_READ|PROT_WRITE,
			MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	EXIT_ERROR(bb->full, MAP_FAILED, "Error mmap");
	sem_init(bb->full, 1, N);

	// Worker generation
	for (int i = 0; i < W; i++) {
		EXIT_ERROR(pid = fork(), -1, "Error fork");
		if WORKER(pid) {
			worker(bb);
		}
	}

	// Collector generation
	EXIT_ERROR(pid = fork(), -1, "Error fork");
	if COLLECTOR(pid) {
		fprintf(stderr, "Ciao sono il collector!\n");
		return EXIT_SUCCESS;
	}

	//***************** SERVER *****************
	scanfs(path, bb);

	for (int i = 0; i < W; i++) {
		put(STOP_SIGNAL, bb);
	}
	//******************************************
	
	// Spring cleaning
	for (int i = 0; i < W + 1; i++) {
		wait(NULL);
	}
	
	sem_destroy(bb->full);
	sem_destroy(bb->empty);
	sem_destroy(bb->mutex);
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

void static get_cli_input(int argc, char** argv, char* path, size_t* W, size_t* N) {
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
