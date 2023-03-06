#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHECK_ERROR(res, errval, msg) {\
	if (res == errval) { perror(msg); exit(EXIT_FAILURE); }\
}

#define CHECK_READ(res, eof, n)\
	switch (res) {\
		case -1:\
			perror("Errore read");\
			break;\
		case 0:\
			eof = true;\
			break;\
		default:\
			n += res;\
			break;\
	}\

#define BTOS(x) ((x) ? "true" : "false")

int main(void) {
	pid_t pid;
	int padrefiglio[2], figliopadre[2];

	CHECK_ERROR(pipe(padrefiglio), -1, "Errore pipe")
	CHECK_ERROR(pipe(figliopadre), -1, "Errore pipe")

	CHECK_ERROR((pid = fork()), -1, "Errore fork")

	if (pid == 0) {
		close(padrefiglio[1]);
		close(figliopadre[0]);

		size_t len = 0;
		size_t n = 0;
		size_t maxmsglen;
		bool eof = false;
		char* str = NULL;
		ssize_t readres;

		while(true) {
			n = 0;
			maxmsglen = sizeof(size_t);
			do {
				readres = read(padrefiglio[0], &len, maxmsglen - n);
				CHECK_READ(readres, eof, n);
			} while (n < maxmsglen && !eof);	
			if (eof) break;
			
			fprintf(stderr,"len: %lu\n", len);

			CHECK_ERROR((str = (char*)realloc(str, len * sizeof(char))), NULL, "Errore realloc");
			
			n = 0;
			maxmsglen = len * sizeof(char);
			do {
				readres = read(padrefiglio[0], &str[n], maxmsglen - n);
				CHECK_READ(readres, eof, n);
			} while (n < maxmsglen && !eof);	
			if (eof) break;
			
			fprintf(stderr, "str: %s\n", str);
		}

		free(str);
		close(padrefiglio[0]);
		close(figliopadre[1]);
	}
	else {
		close(padrefiglio[0]);
		close(figliopadre[1]);
		
		size_t len = 12;
		char* str = "Hello world!";

		write(padrefiglio[1], &len, sizeof(size_t));
		// CONTROLLO ATOMICO
		write(padrefiglio[1], str, len * sizeof(char));
		// CONTROLLO ATOMICO
		
		close(padrefiglio[1]);
		close(figliopadre[0]);
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
