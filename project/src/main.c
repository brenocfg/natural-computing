//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "ind.h"
#include "gen.h"

struct graph *read_input (char *top_filename, char *req_filename) {
	struct graph *graph;
	FILE *top_file, *req_file;

	top_file = fopen(top_filename, "r");
	if (top_file == NULL) {
		fprintf(stderr, "Error reading topology file!\n");
		return NULL;
	}

	req_file = fopen(req_filename, "r");
	if (req_file == NULL) {
		fprintf(stderr, "Error reading requests file!\n");
		return NULL;
	}

	uint32_t numv, nume;
	if (fscanf(top_file, "%u %u\n", &numv, &nume) != 2) {
		fprintf(stderr, "Badly formatted topology file!\n");
		return NULL;
	}

	uint32_t numr;
	if (fscanf(req_file, "%u\n", &numr) != 1) {
		fprintf(stderr, "Badly formatted requests file!\n");
		return NULL;
	}

	graph = init_graph(numv, numr);

	uint32_t i, v1, v2;
	for (i = 0; i < nume; i++) {
		if (fscanf(top_file, "%u %u\n", &v1, &v2) != 2) {
			fprintf(stderr, "Badly formatted topology file!\n");
			return NULL;
		}
		add_edge(graph, v1, v2);
	}

	for (i = 0; i < numr; i++) {
		if (fscanf(req_file, "%u %u\n", &v1, &v2) != 2) {
			fprintf(stderr, "Badly formatted requests file!\n");
			return NULL;
		}
		add_request(graph, v1, v2);
	}

	fclose(top_file);
	fclose(req_file);

	return graph;
}

int main (int argc, char *argv[]) {
	if (argc < 7) {
		fprintf(stderr, "Usage: %s <topology_file> <request_file>", argv[0]);
		fprintf(stderr, " <num_inds> <num_gen> <tourn_size> <seed>\n");
		return 1;
	}

	struct graph *graph = read_input(argv[1], argv[2]);
	if (graph == NULL) {
		fprintf(stderr, "Fatal error: could not build graph!\n");
		return 1;
	}

	uint32_t num_inds = atoi(argv[3]);
	uint32_t num_gen = atoi(argv[4]);
	uint32_t k = atoi(argv[5]);
	uint32_t seed = atoi(argv[6]);

	srand(seed);

	struct ind **first_pop = init_pop(num_inds, graph);

	fprintf(stderr, "---------- GENERATION 1 ------------\n");
	print_pop(first_pop, num_inds, 1);
	uint32_t out = rwa(first_pop, num_inds, num_gen, k, graph);

	fprintf(stdout, "%d\n", out);

	destroy_graph(graph);

	return 0;
}
