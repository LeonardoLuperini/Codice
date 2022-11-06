/*
 * Scrivere un programma in C che implementa un albero binario di ricerca contenente numeri interi.
 * Definire la struttura di dati necessaria. Implementare le seguente funzioni:
 * -insert - prende un albero binario di ricerca e inserisce un nuovo elemento
 * 
 * -printAscending - prende un albero binario di ricerca e stampa gli elementi in ordine crescente,
 *  visitando l'albero tutti sulla stessa riga separati da spazio.
 * 
 * -find - prende in albero e un elemento, e restituisce 1 se l'elemento esiste, 0 altrimenti 
 * 
 * Implementare una funzione main che esegue le operazioni:
 * -legge da standard input un numero intero n seguito da n interi, e li inserisce in un nuovo albero.
 * -stampa gli elementi in ordine crescente 
 * -legge un altro numero intero e controlla se esiste nell'albero, stampando True se trovato o False altrimenti.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
	int val;
	struct Nodo* left;
	struct Nodo* right;
} Nodo;

typedef Nodo* NodoPtr;

void insert(NodoPtr* T, int val);
void printAscending(NodoPtr T);
int find(NodoPtr T, int val);
int readInt();

int main() {
	NodoPtr T = NULL;
	int n = readInt();

	for (int i = 0; i < n; i++) insert(&T, readInt());
	
	printAscending(T);
	if (n > 0) printf("\n");
	
	if ( find(T, readInt()) ) printf("True\n");
	else printf("False\n");

	return 0;
}

void insert(NodoPtr* T, int val) {
	if ((*T) == NULL) {
		NodoPtr newNodoPtr = (NodoPtr) malloc(sizeof(Nodo));
		newNodoPtr->val = val;
		newNodoPtr->left = NULL;
		newNodoPtr->right = NULL;
		(*T) = newNodoPtr;
	}
	else if ((*T)->val >= val) insert( &( (*T)->left ), val);
	else insert( &( (*T)->right ), val);
}

void printAscending(NodoPtr T) {
	if (T == NULL) return;
	printAscending(T->left);
	printf("%d ", T->val);
	printAscending(T->right);
}

int find(NodoPtr T, int val) {
	if (T == NULL) return 0;
	else if (T->val == val) return 1;
	else if (T->val > val) return find(T->left, val);
	else return find(T->right, val);
}

int readInt() {
	int x;
	while (!( scanf("%d", &x) )) {
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]");
	}
	return x;
}
