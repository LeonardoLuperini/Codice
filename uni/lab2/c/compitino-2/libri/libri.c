#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 110
#define IN "libri.txt"

typedef struct {
	char nome[N];
	char autore[N];
	int anno;
	int quantita;
} Libro;

int cmpLibNome(const void* a, const void* b) {
	Libro* l1 = (Libro*) a;
	Libro* l2 = (Libro*) b;

	return strcmp(l1->nome, l2->nome);
}

int cmpLibAnno(const void* a, const void* b) {
	Libro* l1 = (Libro*) a;
	Libro* l2 = (Libro*) b;

	return l1->anno - l2->anno;
}

int main() {
	Libro libri[N];
	char buf[N*3];
	size_t i = 0;

	FILE* f = fopen(IN, "r");
	if (f) {
		while(!feof(f)) {
			if(fgets(buf, sizeof(buf), f) != NULL) {
				strcpy(libri[i].nome, strtok(buf, ","));
				strcpy(libri[i].autore, strtok(NULL, ","));
				libri[i].anno = atoi(strtok(NULL, ","));
				libri[i].quantita = atoi(strtok(NULL, ","));
				i++;
			}
		}

		qsort(libri, i, sizeof(Libro), cmpLibNome);
		qsort(libri, i, sizeof(Libro), cmpLibAnno);
		
		for (int j = 0; j < i; j++) {
			if(libri[j].quantita == 0) {
				printf("%s di %s (%d)\n", libri[j].nome, libri[j].autore, libri[j].anno);
			}
		}
		
		fclose(f);
	} else printf("Apertura file voti1.txt: No such file or directory\n");

	return 0;
}
