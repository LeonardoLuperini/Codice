#include "stack.h"

void push(Stack* t, int val) {
	Stack newTop = (Stack) malloc(sizeof(StackNode));
	if (newTop) {
		newTop->index = val;
		newTop->next = (*t);
		(*t) = newTop;
	}
	else {
		puts("Error: No more memory available!");
		exit(1);
	} 
}

int pop(Stack* t) {
	if (*t) {
		Stack temp = (*t)->next;
		int val = (*t)->index;
		free((*t));
		(*t) = temp;
		return val;
	} else return -1;
}
