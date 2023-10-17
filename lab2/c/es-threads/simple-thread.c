#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define EXIT_ERROR(val, errval, msg) if ((val) == (errval)) {perror((msg)); exit(EXIT_FAILURE);}
#define USELESS_ARG(arg) (arg) = NULL; free((arg));

void* f(void* arg) {
	USELESS_ARG(arg);
	printf("Sono il thread %lu\n", pthread_self());
	return NULL;
}

int main(int argc, char** argv) {
	size_t n;
	pthread_t* t;
	if (argc != 2) {
		fprintf(stderr, "Numero errato di patametri!\nLa sintassi correta è %s <n. of thread>\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	n = atoi(argv[1]);
	t = malloc(n * sizeof(pthread_t));

	for(size_t i = 0; i < n; i++) pthread_create(&(t[i]), NULL, f, NULL);
	for(size_t i = 0; i < n; i++) pthread_join(t[i], NULL);

	free(t);
	return EXIT_SUCCESS;
}
