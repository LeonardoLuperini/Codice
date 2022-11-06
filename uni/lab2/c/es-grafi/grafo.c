#include "grafo.h"

int main() {
	Graph g = load("grafo.txt");

	//Calcolo roba
	
	save(g, "nuovo-grafo.txt");

	return EXIT_SUCCESS;
}

Graph load(char* file) {
	FILE* input = fopen(file, "r");
	
	if(input) {
		Graph g;
		fscanf(input, "%d", &g.N);

		g.nodes = (Node*) malloc(g.N * sizeof(Node));
		
		for (int i = 0; i < g.N; i++) {
			fscanf(input, "%d", g.nodes[i].val);
			g.nodes[i].adjList = NULL;
		}

		int n1, n2;
		float w;
		while (fscanf(input, "%d %d %f", n1, n2, w) == 3) {

		}

	}

	return g;
}

void save(Graph g, char* file) {

}
