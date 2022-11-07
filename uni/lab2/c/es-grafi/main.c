#include "grafo.h"

int main() {
	Graph g = load("grafo.txt");

	//Calcolo roba
	
	save(g, "nuovo-grafo.txt");

	return EXIT_SUCCESS;
}
