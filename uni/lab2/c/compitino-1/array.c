#include <stdio.h>
#include <stdlib.h>

int readInt();
void printArr(int arr[], int n);
void sommaArr(int arr[], int n, int b[]);

int main() {
	int n;
	n = readInt();
	int a[n];
	
	for(int i = 0; i < n; i++){
		a[i] = readInt();
	}

	int b[n-1];
	sommaArr(a, n, b);
	printArr(b, n-1);

}

int readInt() {
	int x;
	while (!( scanf("%d", &x) )) {
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]");
	}
	return x;
}

void printArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}

void sommaArr(int arr[], int n, int b[]) {
	for(int i = 0; i < n-1; i++){
		b[i] = arr[i] + arr[i+1];
	}
}

