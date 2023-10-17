#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) {perror((msg)); exit(EXIT_FAILURE);}
#define USELESS_ARG(arg) (arg) = NULL; free((arg));

typedef struct {
	unsigned long counter;
	sem_t mtx;
} barrier_t;

void* f(void*);
void barrier_init(barrier_t* bar, size_t n);
void barrier_wait(barrier_t* bar);

int main(int argc, char** argv) {
	size_t n;
	pthread_t* tid;
	barrier_t bar;

	if (argc != 2) {
		fprintf(stderr, "Numero errato di patametri!\nLa sintassi correta è %s <n. of thread>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	tid = malloc(n * sizeof(pthread_t));
	barrier_init(&bar, n);

	for(size_t i = 0; i < n; i++) pthread_create(&(tid[i]), NULL, f, (void*)&bar);
	for(size_t i = 0; i < n; i++) pthread_join(tid[i], NULL);

	free(tid);
	return EXIT_SUCCESS;
}

void* f(void* arg) {
	pthread_barrier_t* bar = (pthread_barrier_t*)arg;
	printf("Sono il thread numero %lu\n", pthread_self());
	barrier_wait(&bar);
	printf("Fine barriera lol!\n");
	return NULL;
}

void barrier_init(barrier_t* bar, size_t n) {

	bar = malloc(n * sizeof());

}

void barrier_wait(barrier_t* bar) {
	bar--;
}
