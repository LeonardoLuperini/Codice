#include <stdio.h>

#define N 10
#define BUFF 1000

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
		printf("Vuoi leggere un file:\n\t0 - di testo\n\t1 - binario\n->");
		n = readInt();
		if (n == 0 ) {
			char str[BUFF];
			FILE* file = fopen("file.txt", "r");
			if (!file) return 1;
			
			while(!feof(file) && fscanf(file ,"%s", str)) printf("%s", str);

			fclose(file);	
		} else if (n == 1) {
			int buf[N];
			FILE* file = fopen("file.b", "rb");
			if (!file) return 1;
			
			fread(buf, sizeof(int), N, file);

			for (int i = 0; i < N; i++)	printf("%d: %d\n", i, buf[i]);

			fclose(file);	
		} else printf("\nErrore! Opzione non valida\n");
	} while(n != 0 && n != 1);

	return 0;
}
