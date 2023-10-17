#include <stdio.h>

#define N 10

int main() {
	FILE* file = fopen("f.txt", "w");
	if (file) {
		int x;
		for(int i = 0; i < N; i++) {
			scanf("%d", &x);
			fprintf(file, "%d,", x);
		}
		fclose(file);
	}
	else {
		perror("Errore nell'apertura di f.txt: ");
	} 

}
