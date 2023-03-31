#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
	int val;
	bool scrittore;
	size_t nlettori;
} arg_t;

void* lettore(void* arg) {
	arg_t* a = (arg_t*) arg;
	return NULL;
}

void* scrittore(void* arg) {
	arg_t* a = (arg_t*) arg;
	return NULL;
}

int main(int argc, char** argv) {
	size_t l;
	size_t s;

	if (argc != 3) {
		fprintf(stderr, "Numero errato di patametri!\nLa sintassi correta è %s <n. of thread>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	l = atoi(argv[1]);
	s = atoi(argv[2]);

	pthread_t tid[l + s];

	for(size_t i = 0; i < l; i++) {
		pthread_create(&tid[i], NULL, lettore, NULL);
		
	}
	
	return EXIT_SUCCESS;
}
