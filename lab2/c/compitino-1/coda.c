#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef Node* NodePtr;

void push(NodePtr* headPtr, NodePtr* tailPtr, int val);
void pop(NodePtr* headPtr, NodePtr* tailPtr);

int peak(NodePtr head);
void print(NodePtr head);
int length(NodePtr head);

bool isEven(int n) { return (bool)(!(n%2)); }
int readInt();

int main (){
    NodePtr tail = NULL, head = NULL;
	int zero = 0, x;
	
	do {
		x = readInt();
		if (x == 0) {
			zero++;
			if ( length(head) >= 4 || isEven(peak(head)) ) pop(&head, &tail);
			if (zero == 2) break;
		}
		else {
			zero = 0;
			if (isEven(x)) push(&head, &tail, x/2);
			else push(&head, &tail, x);
		}
	} while (true);
	printf("Lista con %d elementi\n", length(head));
	print(head);

    return 0;
}

void push(NodePtr* headPtr, NodePtr* tailPtr, int val) {
	NodePtr newNode = (NodePtr) malloc(sizeof(Node));
	if (newNode != NULL) {
		newNode->val = val;
		newNode->next = NULL;
		if (*tailPtr != NULL) (*tailPtr)->next = newNode;
		if (*headPtr == NULL) *headPtr = newNode;
		*tailPtr = newNode;
	}
}

void pop(NodePtr* headPtr, NodePtr* tailPtr) {
	if (*headPtr != NULL) {
		NodePtr oldNode = *headPtr;
		*headPtr = (*headPtr)->next;
		if(*headPtr == NULL) *tailPtr = NULL;
		free(oldNode);
	}
}

int peak(NodePtr head) {
	return (head == NULL) ? 0 : head->val;
}

void print(NodePtr head) {
	if (head != NULL) {
		printf("%d\n", peak(head));
		print(head->next);
	}
}

int length(NodePtr head) { return (head == NULL) ? 0 : 1 + length(head->next); }

int readInt() {
	int x;
	while (!( scanf("%d", &x) )) {
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]");
	}
	return x;
}
