#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define IN "input.txt"
#define N 101

int main() {
	char buf[N];
	FILE* f = fopen(IN, "r");
	size_t buflen, nseq = 0, maxseq = 0, nuctot = 0, lseq = 0;
	
	while (!feof(f)) {
		buflen = fgets(f, "%s", buf);
		printf("%s\n", buf);	
		if (buf[0] != '>' ) {
			if (!(lseq)) nseq++;
			lseq += buflen;
			nuctot += buflen;
			maxseq = (lseq > maxseq) ? lseq : maxseq;
		} else lseq = 0;
	}

	fclose(f);

	printf("Numero sequenze: %zu\n", nseq);
	printf("Lunghezza della sequenza più lunga: %zu\n", maxseq);
	printf("Numero totale di nucleotidi: %zu\n", nuctot);

	return 0;
}
