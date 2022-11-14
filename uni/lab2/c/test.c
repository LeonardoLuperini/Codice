#include<stdio.h>

#define N 4

int somma(int a, int b);
int sottrazione(int a, int b);
int moltiplicazione (int a, int b);
int divisione(int a, int b);

int main() {
	int (*f[N])(int, int) = {somma, sottrazione, moltiplicazione, divisione};
	int i, a, b;
	printf("Cosa vuoi fare?\n-0 sommare -1 sottrarre -2 moltiplicare -3 dividere\n->");
	scanf("%d",&i);
	printf("Inserisci due numeri:");
	scanf("%d %d", &a, &b);
	printf("Risultato:%d\n", f[i](a,b));

	return 0;
}

int somma(int a, int b) {
	return a+b;
}

int sottrazione(int a, int b) {
	return a-b;
}


int moltiplicazione(int a, int b) {
	return a+b;
}

int divisione(int a, int b) {
	return a/b;
}
