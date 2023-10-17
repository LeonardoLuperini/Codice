#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int val;
	struct n* l;
	struct n* r;
} Node;

void visita (Node* root);
void insert (Node** where, int val);

int main () {
	Node root;
	root.val = 1;
	insert(&(root.l), 2);
	insert(&(root.l->l), 3);
	insert(&(root.l->r), 4);
	insert(&(root.l->r->l), 12);
	insert(&(root.r), 5);
	insert(&(root.r->l), 6);
	insert(&(root.r->r), 7);

	visita(&root);

	return 0;
}

void insert (Node** where, int val) { 
	Node* what = malloc(sizeof(Node));
	if (!what) {
		printf("Error: not enough memory!\n");
		exit(1);
	}
	
	what->val = val;
	what->l = NULL;
	what->r = NULL;
	*where = what;
}


/*
void visita (Node* root) {
	if (root == NULL) printf("NULL\n");
	else {
		visita(root->l);
		visita(root->r);
		printf("%d\n", root->val);
	}
}
*/
