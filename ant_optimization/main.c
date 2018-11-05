//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "aco.h"

struct graph *read_input (char *filename) {
	struct graph *graph;
	FILE *input;

	input = fopen(filename, "r");
	if (input == NULL) {
		fprintf(stderr, "Error reading input file!\n");
		return NULL;
	}

	uint32_t numv, nume;
	if (fscanf(input, "%u %u\n", &numv, &nume) != 2) {
		fprintf(stderr, "Badly formatted input!\n");
		return NULL;
	}

	graph = init_graph(numv);

	uint32_t i, v1, v2, weight;
	for (i = 0; i < nume; i++) {
		if (fscanf(input, "%u\t%u\t%u\n", &v1, &v2, &weight) != 3) {
			fprintf(stderr, "Badly formatted input!\n");
			return NULL;
		}
		add_edge(graph, v1-1, v2-1, weight);
	}

	fclose(input);

	return graph;
}

int main (int argc, char *argv[]) {
	if (argc < 6) {
		fprintf(stderr, "Usage: ./aco <input_file> <decay_ratio> <num_ants>");
		fprintf(stderr, " <num_it> <seed>\n");
		return 1;
	}

	double decay = 1.0 - atof(argv[2]);
	uint32_t num_ants = atoi(argv[3]);
	uint32_t num_it = atoi(argv[4]);
	uint32_t seed = atoi(argv[5]);

	struct graph *newgraph = read_input(argv[1]);
	if (newgraph == NULL) {
		fprintf(stderr, "Fatal error: could not build graph!\n");
		return 1;
	}

	srand(seed);
	uint32_t ans = aco_longest(newgraph, decay, num_ants, num_it);
	fprintf(stdout, "%u\n", ans);

	destroy_graph(newgraph);

	return 0;
}
