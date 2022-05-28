#include <stdio.h>
#include <stdbool.h>

typedef struct vertx {
    int data;
    struct Node* nei; //vicinato -> neiborhood
} Vertex;

typedef Vertex* VertexPtr;

typedef struct Node {
    VertexPtr vPtr;
    struct Node *nextPtr;
} Node;

typedef Node* NodePtr;

/**
 * @brief 
 * Inserisce un elemeno in cima alla lista
 * @param listPtr è il puntatore di testa della lista
 * @param vPtr è il vertex che voglio aggiungere alla lista
 */
void listInsert(NodePtr *listPtr, VertexPtr vPtr);
/**
 * @brief 
 * Elemina un elemento dalla lista
 * @param listPtr è il puntatore di testa della lista
 * @param vPtr è il vertex che voglio aggiungere alla lista
 */
void listDelete(NodePtr *listPtr, VertexPtr vPtr);
/**
 * @brief 
 * Controlla se la lista è vuota, se lo è returna false
 * @param listPtr è il puntatore di testa della lista
 * @return true or false
 */
bool listIsEmpty(NodePtr listPtr);
/**
 * @brief
 * Stampa la lsta
 * @param listPtr è il puntatore alla testa della lista
 */
void listPrint(NodePtr listPtr);

int main() {
    VertexPtr firstVert = NULL;
    //gaphInsert(firstVert);
    //gaphInsert(firstVert);

    return 0;
}

void listInsert(NodePtr *listPtr, VertexPtr vPtr) {
    NodePtr nuovoPtr = malloc(sizeof(Node));

    if (nuovoPtr != NULL){
        nuovoPtr->vPtr = vPtr;
        nuovoPtr->nextPtr = *listPtr;
        *listPtr = nuovoPtr;
    } else puts("Memoria finita :(");
}

void listDelete(NodePtr *listPtr, VertexPtr vPtr) {
    NodePtr curPtr = *listPtr, prevPtr = NULL;
    while (curPtr != NULL && vPtr != curPtr->vPtr){ 
        prevPtr = curPtr;
        curPtr = curPtr->nextPtr;
    }
    if (*listPtr == curPtr) *listPtr = (*listPtr)->nextPtr;
    else prevPtr->nextPtr = curPtr->nextPtr; 
    free(curPtr);
}

bool listIsEmpty(NodePtr listPtr) {
    return (listPtr != NULL) ? true : false;
}

void listPrint(NodePtr listPtr){
    printf("\n\n-------\n%s", (listPtr != NULL)?"Head":"Empty");
    while(listPtr != NULL){
        printf("\n%i ",listPtr->vPtr);
        listPtr = listPtr->nextPtr;
    }
    printf("\n-------\n\n");
}