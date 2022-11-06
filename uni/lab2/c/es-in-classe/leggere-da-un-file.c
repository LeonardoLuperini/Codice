#include <stdio.h>

#define N 10

int main() {
	FILE* file = fopen("f.txt", "r+");
	if (file) {	
		int x;
		while ( !feof(file) ) {
			fscanf(file, "%d,", &x);
			printf("%d ", x);
		}
		printf("\n");

		fclose(file);
	}
	else {
		perror("Errore nell'apertura di f.txt: ");
	} 

}
