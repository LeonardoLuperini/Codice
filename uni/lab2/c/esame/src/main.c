#include "error_handling_utils.h"
#include "files.h"
#include "statistic.h"
#include "tsqueue.h"
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else
#define DPRINT(...) ;
#endif

#define CORRECT_SINTAX_MSG(name)                                               \
    printf("The correct syntax is:\n"                                          \
           "\t%s  <n. threads> <path_to_file>\n",                              \
           name);

#define NPRINTF(s, n)                                                          \
    for (int i = 0; i < n; i++)                                                \
        printf("%s", s);                                                       \
    printf("\n");

#define PRINT_HEADER()                                                         \
    printf("%-10s %-10s %-10s %-20s\n", "n", "avg", "std", "file");            \
    NPRINTF("-", 50);

#define STOP 0

static void get_cli_input(int argc, char **argv, size_t *nworker, char **path);
static bool str_is_size(char *str);
static void search_datfiles(char *path, queue_t *files);
static void *worker(void *arg);

int main(int argc, char *argv[]) {
    size_t nworker;
    char *path;
    queue_t *files = queue_init();
    ERR_PRINT_EXIT(files == NULL, "Error queue_init\n");

    get_cli_input(argc, argv, &nworker, &path);
    pthread_t tid[nworker];
    DPRINT("nworker: %lu\n"
           "path: %s\n",
           nworker, path);

    PRINT_HEADER();

    for (size_t i = 0; i < nworker; i++) {
        sthread_create(&tid[i], worker, (void *)files);
    }

    search_datfiles(path, files);
    for (size_t i = 0; i < nworker; i++) {
        ERR_PRINT_EXIT(!queue_push(files, STOP), "Error queue_push\n");
    }

    for (size_t i = 0; i < nworker; i++) {
        sthread_join(tid[i], NULL);
    }

    queue_destroy(files);
    return EXIT_SUCCESS;
}

static void *worker(void *arg) {
    queue_t *files = (queue_t *)arg;
    char *path;
    double *num_array = NULL;
    size_t num_array_len = 0;
    size_t n_of_doubles = 0;
    double average, stdev;

    path = (char *)queue_pop(files);
    while (path != STOP) {
        DPRINT("%lu: %s\n", pthread_self(), path);

        file_to_array(path, &num_array, &num_array_len, &n_of_doubles);
        average = avg(num_array, n_of_doubles);
        stdev = std(num_array, n_of_doubles);
        printf("%lu\t%lf\t%lf\t%s\n", n_of_doubles, average, stdev, path);

        free(path);
        path = (char *)queue_pop(files);
    }

    return EXIT_SUCCESS;
}

static void search_datfiles(char *path, queue_t *files) {
    DIR *dir;
    char *newpath;
    struct dirent *direlem;
    char *fname;
    size_t len_fname;
    char *fext;

    dir = opendir(path);
    ERR_PERROR_EXIT(dir == NULL, "Error opendir");
    while (errno == 0 && (direlem = readdir(dir))) {
        if (IS_SUB_DIR(direlem)) {
            newpath = malloc(sizeof(char) * PATH_MAX);
            ERR_PERROR_EXIT(newpath == NULL, "Error malloc");

            concat_path(path, direlem->d_name, newpath);
            search_datfiles(newpath, files);

            free(newpath);
        }
        if IS_FILE (direlem) {
            fname = direlem->d_name;
            len_fname = strlen(fname);
            fext = fname + len_fname - 4; // TODO: use strrchr
            if (strcmp(fext, ".dat") == 0) {
                newpath = malloc(sizeof(char) * PATH_MAX);
                ERR_PRINT_EXIT(newpath == NULL, "Error malloc\n");
                DPRINT("deb: %s\n", fname);
                concat_path(path, fname, newpath);
                ERR_PRINT_EXIT(!queue_push(files, (void *)newpath),
                               "Error queue_push");
            }
        }
        errno = 0;
    }
    ERR_PERROR_EXIT(errno != 0 && direlem == NULL, "Error readdir")
    closedir(dir);
}

static bool str_is_size(char *str) {
    while (*str) {
        if (!isdigit(*str))
            return false;
        str++;
    }
    return true;
}

static void get_cli_input(int argc, char **argv, size_t *nworker, char **path) {
    if (argc != 3) {
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    // n. of worker
    if (!str_is_size(argv[1])) {
        fprintf(stderr, "%s is not a valid quantity!\n", argv[1]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    sscanf(argv[1], "%lu", nworker);
    if (*nworker == 0) {
        fprintf(stderr, "%s is not a valid quantity!\n", argv[1]);
        CORRECT_SINTAX_MSG(argv[0]);
        exit(EXIT_FAILURE);
    }

    // file path
    *path = argv[2];
}
