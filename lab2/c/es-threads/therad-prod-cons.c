#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 30
#define EMPTY 0
#define FULL 1

typedef struct {
    int val;
    int flag;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
} param_t;

void put(param_t *par, int n) {
    pthread_mutex_lock(&par->mtx);
    while (par->flag == FULL)
        pthread_cond_wait(&par->cond, &par->mtx);
    par->val = n;
    par->flag = FULL;
    pthread_cond_signal(&par->cond);
    pthread_mutex_unlock(&par->mtx);
}

void get(param_t *par, int *n) {
    pthread_mutex_lock(&par->mtx);
    while (par->flag == EMPTY)
        pthread_cond_wait(&par->cond, &par->mtx);
    *n = par->val;
    par->flag = EMPTY;
    pthread_cond_signal(&par->cond);
    pthread_mutex_unlock(&par->mtx);
}

void *produttore(void *arg) {
    param_t *par = (param_t *)arg;

    for (size_t i = 0; i < N; i++) {
        int n = rand() % 100;
        printf("Ho produtto %d\n", n);
        put(par, n);
    }
    put(par, -1);

    return NULL;
}

void *consumatore(void *arg) {
    param_t *par = (param_t *)arg;
    int n;

    get(par, &n);
    while (n != -1) {
        printf("Ho consumato %d\n", n);
        get(par, &n);
    }

    return NULL;
}

int main(void) {
    pthread_t p, c;
    param_t par;
    srand(time(NULL));

    par.flag = EMPTY;
    pthread_mutex_init(&par.mtx, NULL);
    pthread_cond_init(&par.cond, NULL);
    // crea prod
    pthread_create(&p, NULL, produttore, (void *)&par);
    // crea cons
    pthread_create(&c, NULL, consumatore, (void *)&par);
    // fa join
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return EXIT_SUCCESS;
}
