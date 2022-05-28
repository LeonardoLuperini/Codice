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
void rec (NodePtr listPtr);

int main(){
    NodePtr listPtr = NULL;
    stampa(listPtr);
    insert(&listPtr, 5);
    stampa(listPtr);
    insert(&listPtr, 6);
    stampa(listPtr);
    insert(&listPtr, 4);
    stampa(listPtr);
    insert(&listPtr, 5);
    stampa(listPtr);
    delete(&listPtr, 5);
    stampa(listPtr);
    delete(&listPtr, 5);
    stampa(listPtr);
}

void insert(NodePtr *listPtr, int val) {
    NodePtr newNodePtr = malloc(sizeof(Node));
    if (newNodePtr != NULL){

        if ( *listPtr == NULL || (*listPtr)->val > val ){
            newNodePtr->val = val;
            newNodePtr->nextPtr = *listPtr;
            *listPtr = newNodePtr;

        } else insert(&((*listPtr)->nextPtr), val);

    } else puts("Error: Memoria esaurita!");
}

void delete(NodePtr *listPtr, int val) {
    if (*listPtr == NULL || (*listPtr)->val > val) {}
    else if ((*listPtr)->val < val){
        delete(&((*listPtr)->nextPtr), val);
    }
    else {
        NodePtr tempPtr = *listPtr;
        *listPtr = (*listPtr)->nextPtr;
        free(tempPtr);
    }
}

bool isEmpty(NodePtr listPtr) {
    return (listPtr != NULL) ? true : false;
}

void stampa(NodePtr listPtr){
    printf("\n---------");
    if (listPtr != NULL) rec(listPtr);
    else puts("\nEmpty\n---------");
}

void rec (NodePtr listPtr) {
    if (listPtr == NULL) printf("\n---------\n");
    else {
        printf("\n%i", listPtr->val);
        rec(listPtr->nextPtr);
    }
}