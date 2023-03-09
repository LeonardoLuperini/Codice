#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define C 5

int main(void) {
	pid_t pid;

	srand(time(NULL));
	
	for (int i = 0; i < C; i++) {
		switch (pid = fork()) {
			case -1: 
				perror("Errore fork");
				break;
			case 0:
				fprintf(stderr, "%d: Partito\n", getgid());
				sleep(rand()%10);
				return EXIT_SUCCESS;
		}
	}
	
	for (int i = 0; i < C; i++) {
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
