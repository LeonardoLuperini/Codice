#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char cognome[10];
	char nome[10];
	char voto[4];
} Studente;

void printIfPassed(Studente stud){
	if(atoi(stud.voto) >= 18)
		printf("%-10s %-10s %-4s ESAME PASSATO\n",stud.cognome, stud.nome, stud.voto);
}

int main() {
	char temp[100];
	FILE* f = fopen("input.txt", "r");
	Studente stud;

	if (f) {
		while( !(feof(f)) ) {
			fscanf(f, "%s", temp);
			char* tok = strtok(temp, ";");
			if (tok) strcpy(stud.cognome, tok); else continue;
			tok = strtok(NULL, ";");
			if (tok) strcpy(stud.nome, tok); else continue;
			tok = strtok(NULL, ";");
			if (tok) strcpy(stud.voto, tok); else continue;
			printIfPassed(stud);
		}
		fclose(f);
	}
	else {
		printf("Errore! File non aperto");
		exit(1);
	}

	return 0;
}
