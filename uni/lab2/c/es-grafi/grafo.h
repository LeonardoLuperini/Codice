#include <stdlib.h>
#include <stdio.h>

typedef struct e{
	size_t dest;
	float w;
	struct e* next;
} Edge;

typedef struct {
	int val;
	Edge* adjList;
} Node;

typedef struct {
	int N;
	Node* nodes;
} Graph;

int numNodes(FILE* f, int* n);
void insNodes(FILE* f, Graph* g);
Graph load(char* file);
void save(Graph, char*);
