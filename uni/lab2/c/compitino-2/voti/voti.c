#include <stdio.h>
#include <stdlib.h>

#define N 100
#define IN "voti1.txt"

int main() {
	float voto, votipesati = 0, res = 0;
	int cfu, cfutot = 0;
	
	FILE* f = fopen(IN, "r");
	if (f) {
		while(!feof(f)) {
			fscanf(f, "%f %d", &voto, &cfu);
			cfutot += cfu;
			votipesati += (float)(voto * (float)cfu);
		}
		printf("%f\n", (votipesati)/((float)cfutot));
	} else printf("Apertura file voti1.txt: No such file or directory\n");

	return 0;
}
