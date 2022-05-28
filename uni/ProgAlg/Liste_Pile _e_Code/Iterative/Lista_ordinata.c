#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* nextPtr;
} Node;

typedef Node* NodePtr;

void insert(NodePtr *listPtr, int val);
void delete(NodePtr *listPtr, int val);
bool isEmpty(NodePtr listPtr);
void stampa(NodePtr listPtr);

int main () {
    NodePtr listPtr = NULL;
    stampa(listPtr);
    insert(&listPtr, 5);
    stampa(listPtr);
    insert(&listPtr, 6);
    stampa(listPtr);
    insert(&listPtr, 4);
    stampa(listPtr);
    delete(&listPtr, 5);
    stampa(listPtr);

    return 0;
}   

void insert(NodePtr *listPtr, int val) {
    NodePtr newNode = malloc(sizeof(Node));
    NodePtr curPtr = *listPtr, prevPtr = NULL;

    if (newNode != NULL){
        newNode->val = val;
        while (curPtr != NULL && val > curPtr->val){ // * Domanda sull'ordine della prima condizione
            prevPtr = curPtr;
            curPtr = curPtr->nextPtr;
        }
        newNode->nextPtr = curPtr;
        if (prevPtr != NULL) prevPtr->nextPtr = newNode;
        else (*listPtr) = newNode;

    } else puts("Error: Memoria esaurita!");
}

void delete(NodePtr *listPtr, int val) {
    NodePtr curPtr = *listPtr, prevPtr = NULL;
    while (curPtr != NULL && val != curPtr->val){ 
        prevPtr = curPtr;
        curPtr = curPtr->nextPtr;
    }
    if (*listPtr == curPtr) *listPtr = (*listPtr)->nextPtr;
    else prevPtr->nextPtr = curPtr->nextPtr; 
    free(curPtr);
}

bool isEmpty(NodePtr listPtr) {
    return (listPtr != NULL) ? true : false;
}

void stampa(NodePtr listPtr){
    printf("\n\n-------\n%s", (listPtr != NULL)?"Head":"Empty");
    while(listPtr != NULL){
        printf("\n%i ",listPtr->val);
        listPtr = listPtr->nextPtr;
    }
    printf("\n-------\n\n");
}