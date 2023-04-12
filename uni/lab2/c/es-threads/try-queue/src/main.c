#define _GNU_SOURCE
#include "error_handling_utils.h"
#include "tsqueue.h"
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2

void *t1(void *arg);
void *t2(void *arg);

int main(void) {
    pthread_t tid[N];
    queue_t *queue = queue_init();

    pthread_create(&tid[0], NULL, t1, queue);
    pthread_create(&tid[1], NULL, t2, queue);

    for (size_t i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    queue_destroy(queue);
    return EXIT_SUCCESS;
}

void *t1(void *arg) {
    queue_t *queue = (queue_t *)arg;

    for (size_t i = 0; i < 100; i++) {
        fprintf(stderr, "[t1]: %lu\n", i);
        queue_push(queue, (void *)i);
    }

    return EXIT_SUCCESS;
}

void *t2(void *arg) {
    queue_t *queue = (queue_t *)arg;

    for (size_t i = 0; i < 100; i++) {
        fprintf(stderr, "\t[t2]: %lu\n", (size_t)queue_pop(queue));
    }

    return EXIT_SUCCESS;
}
