#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) {perror((msg)); exit(EXIT_FAILURE);}
#define USELESS_ARG(arg) (arg) = NULL; free((arg));

void* f(void*);

int main(int argc, char** argv) {
	size_t n;
	pthread_t* tid;
	pthread_barrier_t bar;
	if (argc != 2) {
		fprintf(stderr, "Numero errato di patametri!\nLa sintassi correta è %s <n. of thread>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]);
	tid = malloc(n * sizeof(pthread_t));
	pthread_barrier_init(&bar, NULL, n);

	for(size_t i = 0; i < n; i++) pthread_create(&(tid[i]), NULL, f, (void*)&bar);
	for(size_t i = 0; i < n; i++) pthread_join(tid[i], NULL);

	pthread_barrier_destroy(&bar);
	free(tid);
	return EXIT_SUCCESS;
}

void* f(void* arg) {
	pthread_barrier_t* bar = (pthread_barrier_t*)arg;
	printf("Sono il thread numero %lu\n", pthread_self());
	pthread_barrier_wait(bar);
	printf("Fine barriera lol!\n");
	return NULL;
}
