#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int val;
    struct Node *prevPtr;
} Node;

typedef Node* NodePtr;

void enqueque(NodePtr *headPtr, NodePtr *tailPtr, int val){
    NodePtr newNodePtr = malloc(sizeof(Node));
    if (newNodePtr != NULL){
        newNodePtr->val = val;
        newNodePtr->prevPtr = NULL;
        if (*tailPtr != NULL) (*tailPtr)->prevPtr = newNodePtr;
        if (*headPtr == NULL) *headPtr = newNodePtr;
        *tailPtr = newNodePtr;
        
    } else puts("Error: Memoria esautita");
}

int dequeque(NodePtr *headPtr, NodePtr *tailPtr){
    NodePtr temp = *headPtr;
    int val = temp->val;
    *headPtr = (*headPtr)->prevPtr;
    free(temp);
    return val;
}

void stampa(NodePtr head){
    printf("\n\n-------\n%s", (head != NULL)?"Head":"Empty");
    while(head != NULL){
        printf("\n%i ",head->val);
        head = head->prevPtr;
    }
    printf("\n-------\n\n");
}

int main (){
    NodePtr tail = NULL, head = NULL;
    stampa(head);
    enqueque(&head, &tail, 5);
    stampa(head);
    enqueque(&head, &tail, 6);
    stampa(head);
    printf("\nHai eliminato: %i", dequeque(&head, &tail));
    stampa(head);
    enqueque(&head, &tail, 7);
    stampa(head);
    printf("\nHai eliminato: %i", dequeque(&head, &tail));
    stampa(head);

    return 0;
}