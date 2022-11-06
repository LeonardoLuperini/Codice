#include <stdio.h>
#include <malloc.h>

typedef struct Nodo {
    int val;
    struct Nodo *nextPtr;
} Nodo;

typedef Nodo* NodoPtr;

void stampa(NodoPtr top);
int pop(NodoPtr *topPtr);
void push(NodoPtr *topPtr, int val);

void vpop(char* msg, NodoPtr *topPtr);
void vpush(NodoPtr *topPtr, int val);

int main() {
    printf("\n");
    
    NodoPtr top = NULL;

    stampa(top);

    vpush(&top, 5);
    
    stampa(top);

    vpush(&top, 6);

    stampa(top);

    vpush(&top, 7);

    stampa(top);

    printf("\nHai eliminato: %i",pop(&top));
    
    stampa(top);

    printf("\nHai eliminato: %i",pop(&top));
    
    stampa(top);

    printf("\nHai eliminato: %i",pop(&top));
    
    stampa(top);
    
    
    printf("\n\n");
    return 0;
}

int pop(NodoPtr *topPtr) {
    int val = (*topPtr)->val;
    NodoPtr tempPtr = *topPtr;

    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);
    
    return val;
}

void stampa(NodoPtr top) {
    printf("\n\n-------\n%s", (top != NULL)?"Top":"Empty");
    while (top != NULL){
        printf("\n%d", top->val);
        top = top->nextPtr;
    };
    printf("\n-------\n");
}

void push(NodoPtr *topPtr, int val) {
    NodoPtr nuovoPtr = (NodoPtr)malloc(sizeof(Nodo));

    if (nuovoPtr != NULL){
        nuovoPtr->val = val;
        nuovoPtr->nextPtr = *topPtr;
        *topPtr = nuovoPtr;
    } else puts("Memoria finita :(");
}

void vpush(NodoPtr *topPtr, int val) {
	push(topPtr, val);
	printf("\nHai inserito: %d", val);

}
