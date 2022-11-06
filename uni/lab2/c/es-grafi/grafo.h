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

Graph load(char* file);
void save(Graph, char*);

