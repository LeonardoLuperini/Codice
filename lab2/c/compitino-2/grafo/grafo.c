#include <stdio.h>
#include <stdlib.h>

#define IN "graph.dat"

int main() {
	int n;

	FILE* f = fopen(IN, "rb");
	if (f) {
		fread(&n, sizeof(int), 1, f);
		int nodi[n];
		int matrice[n][n];
		for (int i = 0; i < n; i++) { fread(&(nodi[i]), sizeof(int), 1, f); }
		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) {
				fread(&(matrice[i][j]), sizeof(int), 1, f);
			}
		}

		
		for (int i = 0; i < n; i++) { 
			for (int j = 0; j < n; j++) {
				printf("%d",matrice[i][j]);
			}
			printf("\n");
		}
		fclose(f);
	} else printf("Apertura file vendite1.dat: No such file or directory\n");

	return 0;
}
