#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printanddie(int signum) {
    if (signum == SIGKILL) {
        printf("Ho ricevuto SIGKILL\n");
    }
    if (signum == SIGINT) {
        printf("Ho ricevuto SIGINT\n");
    }
    exit(EXIT_FAILURE);
}

int main(void) {
    size_t counter = 0;
    struct sigaction sa;
    sa.sa_handler = printanddie;
    sigaction(SIGINT, &sa, NULL);
    while (true) {
        sleep(1);
        printf("counter = %lu\n", counter++);
    }
    return EXIT_SUCCESS;
}
