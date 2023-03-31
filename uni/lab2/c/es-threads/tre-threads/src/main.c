#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FILETOREAD "bible.txt"

#ifndef EXIT_ERR
#define EXIT_ERR(val, errval, msg)                                             \
    if ((val) == (errval)) {                                                   \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    }
#endif

#ifndef EXIT_FREE_ERR
#define EXIT_FREE_ERR(val, errval, ptr, msg)                                   \
    if ((val) == (errval)) {                                                   \
        free(ptr);                                                             \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    }
#endif

// static string
typedef struct {
    size_t len;
    char *str;
} sstr_t;

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
    EXIT_ERR(fd = fopen(fname, "r"), NULL, "Error fopen");
    EXIT_FREE_ERR(getline(&line.str, &line.len, fd), -1, line.str,
                  "Error getline");
    printf("%s\n", line.str);

    EXIT_ERR(fclose(fd), EOF, "Error fclose");

    return EXIT_SUCCESS;
}
