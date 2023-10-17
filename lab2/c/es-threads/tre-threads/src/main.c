#define _GNU_SOURCE
#include "error_handling_utils.h"
#include "tsqueue.h"
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILETOREAD "bible.txt"
#define STOP "fermatistop"
#define N 2

// static string
typedef struct {
    size_t len;
    char *str;
} sstr_t;

typedef struct {
    char *filename;
    queue_t *queue_lines;
} arg1_t;

typedef struct {
    queue_t *queue_lines;
    queue_t *queue_words;
} arg2_t;

/* Works like getline but return 0 if EOF,
 * return -1 if error, and 1 otherwise
 */
ssize_t getlineerr(char **lineptr, size_t *n, FILE *stream);
void *t1(void *arg);
void *t2(void *arg);

int main(void) {
    // MANCANO I CONTROLLI
    pthread_t tid[N];
    queue_t *queue_lines = queue_init();
    queue_t *queue_words = queue_init();

    arg1_t arg1;
    arg1.filename = FILETOREAD;
    arg1.queue_lines = queue_lines;

    arg2_t arg2;
    arg2.queue_lines = queue_lines;
    arg2.queue_words = queue_words;

    // T1
    // Apre il file, legge le righe e le carica nella coda delle righe.
    pthread_create(&tid[0], NULL, t1, &arg1);
    // T2
    // Legge la coda delle righe, tokenizza la stringa in parole e la inserisce
    // nalla coda delle parole.
    pthread_create(&tid[1], NULL, t2, &arg2);

    // T3
    // Stampa le parole nella lista delle parole.

    for (size_t i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    queue_destroy(queue_lines);
    queue_destroy(queue_words);
    return EXIT_SUCCESS;
}

void *t1(void *arg) {
    arg1_t *arg1 = (arg1_t *)arg;
    char *fname = arg1->filename;
    queue_t *queue = arg1->queue_lines;
    FILE *fd;
    ssize_t glres;
    sstr_t line;
    line.str = NULL;
    line.len = 0;
    size_t c = 0;

    ERR_PERROR_EXIT((fd = fopen(fname, "r")) == NULL, "Error fopen");

    while (c < 20 && (glres = getlineerr(&line.str, &line.len, fd)) != 0) {
        queue_push(queue, (void *)line.str);
        c++;
        line.str = NULL;
        line.len = 0;
    }
    ERR_FREE_EXIT(glres == -1, line.str, "Error getlineerr");

    ERR_PERROR_EXIT(fclose(fd) == EOF, "Error fclose");

    queue_push(queue, STOP);

    return EXIT_SUCCESS;
}

void *t2(void *arg) {
    arg2_t *arg2 = (arg2_t *)arg;
    queue_t *queue_lines = arg2->queue_lines;
    queue_t *queue_words = arg2->queue_words;
    char *stringa, *str_mod, *tok;

    stringa = (char *)queue_pop(queue_lines);
    while (strcmp(stringa, STOP)) {
        str_mod = stringa;
        tok = strtok(str_mod, " ");
        while (tok != NULL) {
            if (sizeof tok == sizeof(char) && !isspace(tok))
                printf("%s\n", tok);
            else
                printf("%s\n", tok);
            tok = strtok(NULL, " ");
        }
        free(stringa);
        stringa = (char *)queue_pop(queue_lines);
    }

    return EXIT_SUCCESS;
}

ssize_t getlineerr(char **lineptr, size_t *n, FILE *stream) {
    errno = 0;
    ssize_t glres = getline(lineptr, n, stream);
    if (glres == -1 && errno == 0) {
        return 0;
    } else if (glres != -1 && errno == 0) {
        return 1;
    } else {
        return -1;
    }
}
