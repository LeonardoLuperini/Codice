#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 50

typedef char* str;

typedef struct {
	str nome;
	int voto;
} Studente;

void ordinaStudenti(Studente* a);

int main() {
	Studente res[N];
	char n1[N], n2[N];
	size_t sv = 0; //studenti votati
	bool is_in1 = false, is_in2 = false; 

	FILE* f = fopen("input.txt","r");
	
	// creiamo l'array
	while (f && !feof(f)) {
		fscanf(f,"%s,%s", n1, n2);
		for (int i = 0; i < sv; i++){
			if (!strcmp(res[i].nome, n1)) {
				res[i].nome++;
				is_in1 = true; 
			} else if (!strcmp(res[i].nome, n2)) {
				res[i].nome++;
				is_in2 = true; 

			} 
		}

		if (!is_in1) {
			strcpy(res[sv].nome, n1);
			res[sv].voto = 1;
			sv++;
		}

		if (!is_in2) {
			strcpy(res[sv].nome, n2);
			res[sv].voto = 1;
			sv++;
		}

		return 0;
	}

	//ordino l'array
	ordinaStudenti(res);
	
	//stampiamo il risultato
}
