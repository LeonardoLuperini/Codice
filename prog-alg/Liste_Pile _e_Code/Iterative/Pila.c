#include <stdio.h>
#include <malloc.h>

typedef struct Nodo {
    int val;
    struct Nodo *nextPtr;
} Nodo;

typedef Nodo* NodoPtr;

void push(NodoPtr *topPtr, int val) {
    NodoPtr nuovoPtr = malloc(sizeof(Nodo));

    if (nuovoPtr != NULL){
        nuovoPtr->val = val;
        nuovoPtr->nextPtr = *topPtr;
        *topPtr = nuovoPtr;
    } else puts("Memoria finita :(");
}

int pop(NodoPtr *topPtr) {
    int val = (*topPtr)->val;
    NodoPtr tempPtr = *topPtr; // * Prechè qua non uso malloc per dichiarare tempPtr? Forse perchè non lo devo creare perchè lo ho già?
    
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

int main() {
    printf("\n");
    
    NodoPtr top = NULL;

    stampa(top);

    push(&top, 5);
    
    stampa(top);

    push(&top, 6);

    stampa(top);

    push(&top, 7);

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