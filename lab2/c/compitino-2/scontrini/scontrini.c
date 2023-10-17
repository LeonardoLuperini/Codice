#include <stdio.h>
#include <stdlib.h>

#define N 100
#define IN "vendite1.dat"

int main() {
	float v, vtot = 0;

	FILE* f = fopen(IN, "rb");
	if (f) {
		while(!feof(f)) {
			fread(&v, sizeof(v), 1, f);
			vtot += v;
		}
		printf("Totale: %f", vtot);
		fclose(f);
	} else printf("Apertura file vendite1.dat: No such file or directory\n");

	return 0;
}
