#define _GNU_SOURCE
#include "file.h"
#include "pthread_utils.h"
#include "tsqueue.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "__fermatistop__"
#define MAX_BASE_PATH 500

#define CORRECT_SINTAX_MSG(name)                                               \
    printf("The correct syntax is:\n"                                          \
           "\t%s  <n. threads> <dim. buffer> <directory>\n",                   \
           name);

static void get_cli_input(int argc, char **argv, size_t *nthreads,
                          size_t *dimfile, char **path);
static bool str_is_size(char *str);

static void *worker(void *arg) {
    queue_t *queue = (queue_t *)arg;
    char *path = (char *)queue_pop(queue);

    while (strcmp(path, STOP)) {
        fprintf(stderr, "[t: %lu] %s\n", pthread_self(), path);
        path = (char *)queue_pop(queue);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    size_t nthreads, dimfile;
    char *path;
    queue_t *file_queue;
    DIR *dir;
    struct dirent *res_readdir;
    char *filepath;

    get_cli_input(argc, argv, &nthreads, &dimfile, &path);
    nthreads--;
    pthread_t tid[nthreads];

    fprintf(stderr, "path: %s\n", path);

    file_queue = queue_init();

    for (size_t i = 0; i < nthreads; i++) {
        sthread_create(&tid[i], worker, (void *)file_queue);
    }

    ERR_PERROR_EXIT((dir = opendir(path)) == NULL, "Error opendir");
    while (true) {
        // Get res_readdir adn check for errors
        errno = 0;
        res_readdir = readdir(dir);
        ERR_PERROR_EXIT((res_readdir == NULL && errno != 0), "Error readdir");

        // Break if it's had read all files
        if (res_readdir == NULL && errno == 0)
            break;

        // Skip if it's not a file
        if (!IS_FILE(res_readdir))
            continue;

        // Push the new file path
        filepath = malloc(sizeof(char) *
                          (strlen(path) + strlen(res_readdir->d_name) + 10));
        concat_path(path, res_readdir->d_name, filepath);
        queue_push(file_queue, (void *)filepath);
    }

    for (size_t i = 0; i < nthreads; i++) {
        queue_push(file_queue, STOP);
    }

    for (size_t i = 0; i < nthreads; i++) {
        sthread_join(tid[i], NULL);
    }

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

static void get_cli_input(int argc, char **argv, size_t *nthreads,
                          size_t *dimfile, char **path) {
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

    // dim. of files
    if (!str_is_size(argv[2])) {
        fprintf(stderr, "%s is not a valid size!\n", argv[2]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }
    sscanf(argv[2], "%lu", dimfile);
    if (*dimfile == 0) {
        fprintf(stderr, "%s is not a valid size!\n", argv[2]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }
    // folder path
    *path = argv[3];
}
