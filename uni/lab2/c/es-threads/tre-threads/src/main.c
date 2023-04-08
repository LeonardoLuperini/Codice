#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FILETOREAD "bible.txt"

#ifndef EXIT_ERR
#define EXIT_ERR(cond, msg)                                                    \
    if ((cond)) {                                                              \
        perror((msg));                                                         \
        exit(EXIT_FAILURE);                                                    \
    }
#endif

#ifndef EXIT_ERR_FREE
#define EXIT_ERR_FREE(cond, ptr, msg)                                          \
    if ((cond)) {                                                              \
        perror((msg));                                                         \
        free((ptr));                                                           \
        exit(EXIT_FAILURE);                                                    \
    }
#endif

// static string
typedef struct {
    size_t len;
    char *str;
} sstr_t;

/* Works like getline but return 0 if EOF,
 * return -1 if error, and 1 otherwise
 */
ssize_t getlineerr(char **lineptr, size_t *n, FILE *stream);
void *t1(void *arg);

int main(void) {
    // MANCANO I CONTROLLI
    pthread_t tid[3];
    // T1
    // Apre il file, legge le righe e le carica nella coda delle righe
    pthread_create(&tid[0], NULL, t1, FILETOREAD);
    // T2
    // Legge la coda delle righe, tokenizza la stringa in parole e la inserisce
    // nalla coda delle parole

    // T3
    // Stampa le parole nella lista delle parole

    pthread_join(tid[0], NULL);
    /*
for (size_t i = 0; i < 3; i++) {
    pthread_join(tid[i], NULL);
}
    */
    return EXIT_SUCCESS;
}

void *t1(void *arg) {
    char *fname = arg;
    FILE *fd;
    sstr_t line;
    ssize_t glres;
    line.str = NULL;
    line.len = 0;
    size_t c = 0;

    EXIT_ERR((fd = fopen(fname, "r")) == NULL, "Error fopen");

    while ((glres = getlineerr(&line.str, &line.len, fd)) != 0 && c < 100) {
        printf("[%lu]%s", c, line.str);
        c++;
    }
    EXIT_ERR_FREE(glres == -1, line.str, "Error getlineerr");

    free(line.str);
    line.len = 0;
    EXIT_ERR(fclose(fd) == EOF, "Error fclose");

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
