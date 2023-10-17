#include <stdio.h>
#include <stdlib.h>

int readInt();
void fillMat(int* mat[], int r, int c);
void swapMatCol(int* mat[], int c);
void printMat(int* mat[], int r, int c);

int main() {
	int r = readInt();
	int c = readInt();
	int* mat[c];

	if (c != 0 && r != 0) {
		fillMat(mat, r, c);
		swapMatCol(mat, c);
		printMat(mat, r, c);
	}
	
	return 0;
}

int readInt() {
	int x;
	while (!( scanf("%d", &x) )) {
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]");
	}
	return x;
}

void fillMat(int* mat[], int r, int c) {
	for(int j = 0; j < c; j++) {
		mat[j] = (int*)malloc(r * sizeof(int));
		if(mat[j] == NULL) exit(1);
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			mat[j][i] = readInt(); 
		}
	}
}

void swapMatCol(int* mat[], int c) {	
		int* x;
		x = mat[0];
		mat[0] = mat[c-1];
		mat[c-1] = x;
}

void printMat(int* mat[], int r, int c) {
	for(int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", mat[j][i]); 
		}
		printf("\n");
	}
}
