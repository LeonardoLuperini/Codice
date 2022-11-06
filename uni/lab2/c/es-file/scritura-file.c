/* Leggere 10 numeri da tastiera e scriverli in un file. Provare sia con un file testuale sia con un file binario. */

#include <stdio.h>

#define N 10

int readInt() {
	int x;
	while (!( scanf("%d", &x) )) {
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]");
	}
	return x;
}

int main() {
	// Menù
	int n;
	do {
		printf("Vuoi scrivere su un file:\n\t0 - di testo\n\t1 - binario\n->");
		n = readInt();
		if (n == 0 ) {
			FILE* file = fopen("file.txt", "w");
			if (!file) return 1;

			for(int i = 0; i < N; i++) fprintf(file, "%d;", readInt());

			fclose(file);	
		} else if (n == 1) {
			int buf[N];
			FILE* file = fopen("file.b", "wb");
			if (!file) return 1;

			for(int i = 0; i < N; i++) buf[i] = readInt();
			
			fwrite(buf, sizeof(int), N, file);

			fclose(file);	
			
		} else printf("\nErrore! Opzione non valida\n");
	}while(n != 0 && n != 1);

	return 0;
}
