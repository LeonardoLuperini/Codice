#include "error_handling_utils.h"
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sigaction_exit(int signum, const struct sigaction *act,
                    const struct sigaction *oldact) {
    ERR_EXIT(sigaction(signum, act, oldact) == -1, "Error sigaction");
}

static void printanddie(int signum) {
    if (signum == SIGINT) {
        printf("\nResetting alarm\n", SIGINT);
        alarm(3);
    }
    if (signum == SIGTSTP) {
        printf("\nHo ricevuto SIGSTOP: %d\n", SIGSTOP);
        exit(EXIT_SUCCESS);
    }
    if (signum == SIGALRM) {
        printf("\nHo ricevuto SIGALRM: %d\n", SIGALRM);
        exit(EXIT_SUCCESS);
    }
}

int main(void) {
    size_t counter = 0;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = printanddie;
    sigaction_exit(SIGINT, &sa, NULL);
    sigaction_exit(SIGTSTP, &sa, NULL);
    sigaction_exit(SIGALRM, &sa, NULL);
    alarm(3);

    while (true) {
        printf("counter = %lu\n", counter++);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
