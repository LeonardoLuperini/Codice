#define _GNU_SOURCE
#include "file.h"
#include "pthread_utils.h"
#include "selezionaPrimi.h"
#include "tsqueue.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STOP -1
#define MAX_BASE_PATH 500

#define CORRECT_SINTAX_MSG(name)                                               \
    printf("The correct syntax is:\n"                                          \
           "\t%s  <n. threads> <path_to_file> <n. of numbers in the file>\n",  \
           name);

typedef struct {
    queue_t *queue;
    queue_t *queue_prime;
} arg1_t;

static void get_cli_input(int argc, char **argv, size_t *nthreads, char **path,
                          size_t *dimfile);
static bool str_is_size(char *str);

static void *worker(void *arg) {
    arg1_t *arg1 = (arg1_t *)arg;
    queue_t *queue = arg1->queue;
    queue_t *queue_prime = arg1->queue_prime;
    long int *number = (long int *)queue_pop(queue);

    while (number != (long int *)STOP) {
        if (isPrime(*number) && *number != 0) {
            fprintf(stderr, "%ld\n", *number);
            queue_push(queue_prime, (void *)number);
        } else
            free(number);
        number = (long int *)queue_pop(queue);
    }

    queue_push(queue_prime, (void *)STOP);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    size_t nthreads, dimfile;
    char *path;
    queue_t *queue, *queue_prime;
    FILE *fd;
    long int *number;
    arg1_t arg;

    get_cli_input(argc, argv, &nthreads, &path, &dimfile);
    pthread_t tid[nthreads];

    queue = queue_init();
    queue_prime = queue_init();
    arg.queue = queue;
    arg.queue_prime = queue_prime;

    for (size_t i = 0; i < nthreads; i++) {
        sthread_create(&tid[i], worker, (void *)&arg);
    }

    ERR_PERROR_EXIT((fd = fopen(path, "r")) == NULL, "Error fopen");
    while (!feof(fd)) {
        number = malloc(sizeof(long int));
        fread(number, sizeof(long int), 1, fd);
        queue_push(queue, (void *)number);
    }

    for (size_t i = 0; i < nthreads; i++) {
        queue_push(queue, (void *)STOP);
    }

    for (size_t i = 0; i < nthreads; i++) {
        sthread_join(tid[i], NULL);
    }

    size_t stop_counter = 0;
    size_t sum = 0;
    long int array[5000];
    size_t n = 0;
    long int *temp;
    while (stop_counter < nthreads) {
        temp = (long int *)queue_pop(queue_prime);
        if (temp != (long int *)STOP) {
            array[n] = *temp;
            n++;
            free(temp);
        } else
            stop_counter++;
    }

    /*
for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {

    }
}
    */

    for (size_t i = 0; i < n; i++) {
        sum += i * array[i];
    }

    printf("sum: %ld", sum);

    queue_destroy(queue);
    queue_destroy(queue_prime);

    return EXIT_SUCCESS;
}

static bool str_is_size(char *str) {
    while (*str) {
        if (!isdigit(*str))
            return false;
        str++;
    }
    return true;
}

static void get_cli_input(int argc, char **argv, size_t *nthreads, char **path,
                          size_t *dimfile) {
    if (argc != 4) {
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    // n. of threads
    if (!str_is_size(argv[1])) {
        fprintf(stderr, "%s is not a valid quantity!\n", argv[1]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    sscanf(argv[1], "%lu", nthreads);
    if (*nthreads == 0) {
        fprintf(stderr, "%s is not a valid quantity!\n", argv[1]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    // file path
    *path = argv[2];

    // dim. of files
    if (!str_is_size(argv[3])) {
        fprintf(stderr, "%s is not a valid size!\n", argv[3]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }
    sscanf(argv[3], "%lu", dimfile);
}
