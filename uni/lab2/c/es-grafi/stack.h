#include <stdlib.h>
#include <stdio.h>

typedef struct n {
	int index;
	struct n* next;
} StackNode;

typedef StackNode* Stack;

void push(Stack*, int);
int pop(Stack*);
