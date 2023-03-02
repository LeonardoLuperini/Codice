#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int status;
	pid_t pid;
	
	switch (pid = fork()) {
		case -1: 
			perror("Errore fork");
			break;
		case 0:
			printf("%d: eseguendo il figlio\n", getgid());
			break;
		default:
			sleep(10);
			if(waitpid(pid, &status, 0) == -1) {
				perror("Errore nella wait");
				exit(2);
			}
			printf("%d: il figlio ha finito con status %d\n",
					getpid(), WEXITSTATUS(status));
			break;
	}

	return EXIT_SUCCESS;
}
