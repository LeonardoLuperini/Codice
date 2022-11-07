#include "grafo.h"

int numNodes(FILE* f, int* n) {
	return fscanf( f, "%d", n);
}

void insNodes (FILE* f, Graph* g) {
	for (int i = 0; i < g->N; i++) {
		fscanf(f, "%d", &g->nodes[i].val);
		g->nodes[i].adjList = NULL;
	}
}

void insEdge(Graph* g, int n, int d, float w) {
	Edge* edge = (Edge*) malloc(sizeof(Edge));
	edge->dest = d;                                                                                                                                                    
	edge->w = w;
	edge->next = (*g).nodes[n].adjList;
	g->nodes[n].adjList = edge;



	if ((*g).nodes[n].adjList == NULL) {
		
	}
}

void insEdges(FILE* f, Graph* g) {
	int s, e;
	float w;
	
	while (fscanf(f, "%d %d %f", &s, &e, &w) == 3) {
		insEdge(g, s, e, w);	
	}
}

Graph load(char* file) {
	FILE* input = fopen(file, "r");
	
	if(input) {
		Graph g;
		
		numNodes(input, &g.N);

		g.nodes = (Node*) malloc(g.N * sizeof(Node));
		if (! g.nodes) exit(1);
		
		insNodes(input, &g);
		
		insEdges(input, &g);

		return g;
	}
	else exit(1);
}

void save(Graph g, char* file) {

}
