#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
	int val;
	 struct Nodo* next;
} Nodo;

typedef Nodo* NodoPtr;

void insert(int val, NodoPtr* l);
void print(NodoPtr l); 

int main () {
	NodoPtr l=NULL;
	int x;

	do{
		scanf("%d", &x);
		insert(x, &l);
	}while(x>= 0);
	print(l);

	return 0;
}

void insert(int val, NodoPtr* l) {
	NodoPtr 
}
