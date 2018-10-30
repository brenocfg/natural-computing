//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdint.h>
#include <stdio.h>

#include "graph.h"

struct graph *read_input (char *filename) {
	struct graph *graph;
	FILE *input;

	input = fopen(filename, "r");
	if (input == NULL) {
		fprintf(stderr, "Error reading input file!\n");
		return NULL;
	}

	uint32_t numv, nume;
	fscanf(input, "%u %u\n", &numv, &nume);

	graph = init_graph(numv);

	uint32_t i, v1, v2, weight;
	for (i = 0; i < nume; i++) {
		fscanf(input, "%u\t%u\t%u\n", &v1, &v2, &weight);
		add_edge(graph, v1-1, v2-1, weight);
	}

	fclose(input);

	return graph;
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: ./aco <input_file>\n");
		return 1;
	}

	struct graph *newgraph = read_input(argv[1]);

	print_graph(newgraph);

	destroy_graph(newgraph);

	return 0;
}
